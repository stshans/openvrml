/**
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.6.0 MageLang Insitute, 1998
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commerical software.
 * <p>
 * We encourage users to develop software with ANTLR. However,
 * we do ask that credit is given to us for developing
 * ANTLR. By "credit", we mean that if you use ANTLR or
 * incorporate any source code into one of your programs
 * (commercial product, research project, or otherwise) that
 * you acknowledge this fact somewhere in the documentation,
 * research report, etc... If you like ANTLR and have
 * developed a nice tool with the output, please mention that
 * you developed it using ANTLR. In addition, we ask that the
 * headers remain intact in our source code. As long as these
 * guidelines are kept, we expect to continue enhancing this
 * system and expect to make other tools available as they are
 * completed.
 * <p>
 * The ANTLR gang:
 * @version ANTLR 2.6.0 MageLang Insitute, 1998
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 * @author <br><a href="mailto:pete@yamuna.demon.co.uk">Pete Wells</a>
 */

#include "CharScanner.hpp"
#include "CommonToken.hpp"
#include "MismatchedCharException.hpp"
#include <map>

#ifdef HAS_NOT_CCTYPE_H
#include <ctype.h>
#else
#include <cctype>
#endif

#include <iostream>

#ifdef HAS_NOT_CSTRING_H
#include <string>
#else
#include <cstring>
#endif

ANTLR_BEGIN_NAMESPACE(antlr)
ANTLR_C_USING(exit)
ANTLR_C_USING(tolower)

#ifdef ANTLR_REALLY_NO_STRCASECMP
// Apparently, neither strcasecmp nor stricmp is standard, and Codewarrior
// on the mac has neither...
inline int strcasecmp(const char *s1, const char *s2)
{
	while (true)
	{
		char  c1 = tolower(*s1++),
				c2 = tolower(*s2++);
		if (c1 < c2) return -1;
		if (c1 > c2) return 1;
		if (c1 == 0) return 0;
	}
}
#else
#ifdef NO_STRCASECMP
ANTLR_C_USING(stricmp)
#else
ANTLR_C_USING(strcasecmp)
#endif
#endif

CharScannerLiteralsLess::CharScannerLiteralsLess(const CharScanner* theScanner)
: scanner(theScanner)
{}

bool CharScannerLiteralsLess::operator() (const ANTLR_USE_NAMESPACE(std)string& x,const ANTLR_USE_NAMESPACE(std)string& y) const
{
	if (scanner->getCaseSensitiveLiterals()) {
		return ANTLR_USE_NAMESPACE(std)less<ANTLR_USE_NAMESPACE(std)string>()(x,y);
	} else {
#ifdef NO_STRCASECMP
		return (stricmp(x.c_str(),y.c_str())<0);
#else
		return (strcasecmp(x.c_str(),y.c_str())<0);
#endif
	}
}

CharScanner::CharScanner(InputBuffer& cb)
	: saveConsumedInput(true) //, caseSensitiveLiterals(true)
	, literals(CharScannerLiteralsLess(this))
	, inputState(new LexerInputState(cb))
	, commitToPath(false)
	, traceDepth(0)
{
	setTokenObjectFactory(&CommonToken::factory);
}

CharScanner::CharScanner(InputBuffer* cb)
	: saveConsumedInput(true) //, caseSensitiveLiterals(true)
	, literals(CharScannerLiteralsLess(this))
	, inputState(new LexerInputState(cb))
	, commitToPath(false)
	, traceDepth(0)
{
	setTokenObjectFactory(&CommonToken::factory);
}

CharScanner::CharScanner(const LexerSharedInputState& state)
	: saveConsumedInput(true) //, caseSensitiveLiterals(true)
	, literals(CharScannerLiteralsLess(this))
	, inputState(state)
	, commitToPath(false)
	, traceDepth(0)
{
	setTokenObjectFactory(&CommonToken::factory);
}

CharScanner::~CharScanner()
{
}

void CharScanner::append(char c)
{
	if (saveConsumedInput) {
		int l = text.length();
		if ((l%256) == 0) text.reserve(l+256);
		text.replace(l,0,&c,1);
	}
}

void CharScanner::append(const ANTLR_USE_NAMESPACE(std)string& s)
{
	if (saveConsumedInput)
		text+=s;
}

void CharScanner::commit()
{
	inputState->getInput().commit();
}

void CharScanner::consume()
{
	if (inputState->guessing == 0) {
		int c = LA(1);
		if (caseSensitive) {
			append(c);
		} else {
			// use input.LA(), not LA(), to get original case
			// CharScanner.LA() would toLower it.
			append(inputState->getInput().LA(1));
		}
		if (c == '\t') {
			tab();
		}
		else {
			inputState->column++;
		}
	}
	inputState->getInput().consume();
}

/** Consume chars until one matches the given char */
void CharScanner::consumeUntil(int c)
{
	while (LA(1) != EOF_CHAR && LA(1) != c)
	{
		consume();
	}
}

/** Consume chars until one matches the given set */
void CharScanner::consumeUntil(const BitSet& set)
{
	while (LA(1) != EOF_CHAR && !set.member(LA(1))) {
		consume();
	}
}

bool CharScanner::getCaseSensitive() const
{ return caseSensitive; }

//bool CharScanner::getCaseSensitiveLiterals() const
//{ return caseSensitiveLiterals; }

int CharScanner::getColumn() const
{ return inputState->column; }

void CharScanner::setColumn(int c)
{ inputState->column = c; }

bool CharScanner::getCommitToPath() const
{ return commitToPath; }

const ANTLR_USE_NAMESPACE(std)string& CharScanner::getFilename() const
{ return inputState->filename; }

InputBuffer& CharScanner::getInputBuffer()
{ return inputState->getInput(); }

LexerSharedInputState CharScanner::getInputState()
{ return inputState; }

int CharScanner::getLine() const
{ return inputState->line; }

/** return a copy of the current text buffer */
const ANTLR_USE_NAMESPACE(std)string& CharScanner::getText() const
{ return text; }

RefToken CharScanner::getTokenObject() const
{ return _returnToken; }

RefToken CharScanner::makeToken(int t)
{
	RefToken tok=tokenFactory();
	tok->setType(t);
	tok->setColumn(inputState->tokenStartColumn);
	tok->setLine(inputState->tokenStartLine);
	return tok;
}

int CharScanner::mark()
{
	return inputState->getInput().mark();
}

void CharScanner::match(int c)
{
	if ( LA(1) != c ) {
		throw MismatchedCharException(LA(1),c,false,this);
	}
	consume();
}

void CharScanner::match(const BitSet& b)
{
	if (!b.member(LA(1))) {
		throw MismatchedCharException(LA(1),b,false,this);
	}
	consume();
}

void CharScanner::match(const ANTLR_USE_NAMESPACE(std)string& s)
{
	int len = s.length();
	for (int i=0; i<len; i++) {
		if ( LA(1) != s[i] ) {
			throw MismatchedCharException(LA(1),s[i],false,this);
		}
		consume();
	}
}

void CharScanner::matchNot(int c)
{
	if ( LA(1) == c ) {
		throw MismatchedCharException(LA(1),c,true,this);
	}
	consume();
}

void CharScanner::matchRange(int c1, int c2)
{
	if (LA(1)<c1 || LA(1)>c2) {
		throw MismatchedCharException(LA(1),c1,c2,false,this);
	}
	consume();
}

void CharScanner::newline()
{
	++inputState->line;
	inputState->column=1;
}

/** advance the current column number by an appropriate amount.
 *  If you do not override this to specify how much to jump for
 *  a tab, then tabs are counted as one char.  This method is
 *  called from consume().
 */
void CharScanner::tab() {
	// update inputState->column as function of
	// inputState->column and tab stops.
	// For example, if tab stops are columns 1 and 5 etc...
	// and column is 3, then add 2 to column.
	++inputState->column;
}

void CharScanner::panic()
{
	ANTLR_USE_NAMESPACE(std)cerr << "CharScanner: panic" << ANTLR_USE_NAMESPACE(std)endl;
	exit(1);
}

void CharScanner::panic(const ANTLR_USE_NAMESPACE(std)string& s)
{
	ANTLR_USE_NAMESPACE(std)cerr << "CharScanner: panic: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
	exit(1);
}

/** Report exception errors caught in nextToken() */
void CharScanner::reportError(const RecognitionException& ex)
{
	ANTLR_USE_NAMESPACE(std)cerr << ex.toString().c_str() << ANTLR_USE_NAMESPACE(std)endl;
}

/** Parser error-reporting function can be overridden in subclass */
void CharScanner::reportError(const ANTLR_USE_NAMESPACE(std)string& s)
{
	if (getFilename() == "")
		ANTLR_USE_NAMESPACE(std)cerr << "error: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
	else
		ANTLR_USE_NAMESPACE(std)cerr << getFilename().c_str() << ": error: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
}

/** Parser warning-reporting function can be overridden in subclass */
void CharScanner::reportWarning(const ANTLR_USE_NAMESPACE(std)string& s)
{
	if (getFilename() == "")
		ANTLR_USE_NAMESPACE(std)cerr << "warning: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
	else
		ANTLR_USE_NAMESPACE(std)cerr << getFilename().c_str() << ": warning: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
}

void CharScanner::resetText()
{
	text="";
	inputState->tokenStartColumn = inputState->column;
	inputState->tokenStartLine = inputState->line;
}

void CharScanner::rewind(int pos)
{
	inputState->getInput().rewind(pos);
}

void CharScanner::setCaseSensitive(bool t)
{
	caseSensitive = t;
}

void CharScanner::setCommitToPath(bool commit)
{
	commitToPath = commit;
}

void CharScanner::setFilename(const ANTLR_USE_NAMESPACE(std)string& f)
{ inputState->filename=f; }

void CharScanner::setInputState(LexerSharedInputState state)
{ inputState = state; }

void CharScanner::setLine(int l)
{ inputState->line=l; }

void CharScanner::setText(const ANTLR_USE_NAMESPACE(std)string& s)
{ text=s; }

void CharScanner::setTokenObjectFactory(factory_type factory)
{ tokenFactory=factory; }

/** Test the token text against the literals table
 * Override this method to perform a different literals test */
int CharScanner::testLiteralsTable(int ttype) const
{
	ANTLR_USE_NAMESPACE(std)map<ANTLR_USE_NAMESPACE(std)string,int,CharScannerLiteralsLess>::const_iterator i = literals.find(text);
	if (i != literals.end())
		ttype = (*i).second;
	return ttype;
}

/** Test the text passed in against the literals table
 * Override this method to perform a different literals test
 * This is used primarily when you want to test a portion of
 * a token.
 */
int CharScanner::testLiteralsTable(const ANTLR_USE_NAMESPACE(std)string& text_, int ttype) const
{
	ANTLR_USE_NAMESPACE(std)map<ANTLR_USE_NAMESPACE(std)string,int,CharScannerLiteralsLess>::const_iterator i = literals.find(text_);
	if (i != literals.end())
		ttype = (*i).second;
	return ttype;
}

/** Override this method to get more specific case handling */
int CharScanner::toLower(int c) const
{
	return tolower(c);
}

void CharScanner::traceIndent()
{
	for( int i = 0; i < traceDepth; i++ )
		ANTLR_USE_NAMESPACE(std)cout << " ";
}

void CharScanner::traceIn(const ANTLR_USE_NAMESPACE(std)string& rname)
{
	traceDepth++;
	traceIndent();
	ANTLR_USE_NAMESPACE(std)cout << "> lexer " << rname.c_str() << "; c==" << LA(1) << ANTLR_USE_NAMESPACE(std)endl;
}

void CharScanner::traceOut(const ANTLR_USE_NAMESPACE(std)string& rname)
{
	traceIndent();
	ANTLR_USE_NAMESPACE(std)cout << "< lexer " << rname.c_str() << "; c==" << LA(1) << ANTLR_USE_NAMESPACE(std)endl;
	traceDepth--;
}

void CharScanner::uponEOF()
{
}

#ifndef NO_STATIC_CONSTS
const int CharScanner::NO_CHAR;
const int CharScanner::EOF_CHAR;
#endif

ANTLR_END_NAMESPACE

