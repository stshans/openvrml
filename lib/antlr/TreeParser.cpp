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
#include "TreeParser.hpp"
#include "ASTNULLType.hpp"
#include "MismatchedTokenException.hpp"
#include <iostream>

ANTLR_BEGIN_NAMESPACE(antlr)
ANTLR_C_USING(exit)

TreeParser::TreeParser()
: inputState(new TreeParserInputState()), traceDepth(0)
{
}

TreeParser::TreeParser(const TreeParserSharedInputState& state)
: inputState(state), traceDepth(0)
{
}

TreeParser::~TreeParser()
{
}

void TreeParser::setTokenNames(const char** tokenNames_)
{
	while (*tokenNames_) {
		tokenNames.push_back(*(tokenNames_++));
	}
}

/** The AST Null object; the parsing cursor is set to this when
 *  it is found to be null.  This way, we can test the
 *  token type of a node without having to have tests for null
 *  everywhere.
 */
RefAST TreeParser::ASTNULL(new ASTNULLType);

/** Get the AST return value squirreled away in the parser */
//RefAST getAST() const {
//	return returnAST;
//}

void TreeParser::match(RefAST t, int ttype)
{
	if (!t || t==ASTNULL || t->getType()!=ttype)
		throw MismatchedTokenException();
}

/**Make sure current lookahead symbol matches the given set
 * Throw an exception upon mismatch, which is caught by either the
 * error handler or by the syntactic predicate.
 */
void TreeParser::match(RefAST t, const BitSet& b)
{
	if ( !t || t==ASTNULL || !b.member(t->getType()) ) {
		throw MismatchedTokenException();
	}
}

void TreeParser::matchNot(RefAST t, int ttype)
{
	//ANTLR_USE_NAMESPACE(std)cout << "match(" << ttype << "); cursor is " << t.toString() << ANTLR_USE_NAMESPACE(std)endl;
	if ( !t || t==ASTNULL || t->getType()==ttype ) {
		throw MismatchedTokenException();
	}
}

void TreeParser::panic()
{
	ANTLR_USE_NAMESPACE(std)cerr << "TreeWalker: panic" << ANTLR_USE_NAMESPACE(std)endl;
	exit(1);
}

/** Parser error-reporting function can be overridden in subclass */
void TreeParser::reportError(const RecognitionException& ex)
{
	ANTLR_USE_NAMESPACE(std)cerr << ex.toString().c_str() << ANTLR_USE_NAMESPACE(std)endl;
}

/** Parser error-reporting function can be overridden in subclass */
void TreeParser::reportError(const ANTLR_USE_NAMESPACE(std)string& s)
{
	ANTLR_USE_NAMESPACE(std)cerr << "error: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
}

/** Parser warning-reporting function can be overridden in subclass */
void TreeParser::reportWarning(const ANTLR_USE_NAMESPACE(std)string& s)
{
	ANTLR_USE_NAMESPACE(std)cerr << "warning: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
}

/** Specify an object with support code (shared by
 *  Parser and TreeParser.  Normally, the programmer
 *  does not play with this, using setASTNodeType instead.
 */
//	void TreeParser::setASTFactory(ASTFactory f);

/** Specify the type of node to create during tree building */
void TreeParser::setASTNodeFactory(ASTFactory::factory_type factory)
{
	astFactory.setASTNodeFactory(factory);
}

/** Procedure to write out an indent for traceIn and traceOut */
void TreeParser::traceIndent()
{
	for( int i = 0; i < traceDepth; i++ )
		ANTLR_USE_NAMESPACE(std)cout << " ";
}

void TreeParser::traceIn(const ANTLR_USE_NAMESPACE(std)string& rname, RefAST t)
{
	traceDepth++;
	traceIndent();

	ANTLR_USE_NAMESPACE(std)cout << "> " << rname.c_str()
			<< "(" << (t ? t->toString().c_str() : "null") << ")"
			<< ((inputState->guessing>0)?" [guessing]":"")
			<< ANTLR_USE_NAMESPACE(std)endl;
}

void TreeParser::traceOut(const ANTLR_USE_NAMESPACE(std)string& rname, RefAST t)
{
	traceIndent();

	ANTLR_USE_NAMESPACE(std)cout << "< " << rname.c_str()
			<< "(" << (t ? t->toString().c_str() : "null") << ")"
			<< ((inputState->guessing>0)?" [guessing]":"")
			<< ANTLR_USE_NAMESPACE(std)endl;

	traceDepth--;
}

ANTLR_END_NAMESPACE
