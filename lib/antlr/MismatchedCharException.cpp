/**
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.6.0 MageLang Insitute, 1999
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
 * @version ANTLR 2.6.0 MageLang Insitute, 1999
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 * @author <br><a href="mailto:pete@yamuna.demon.co.uk">Pete Wells</a>
 */

#include "MismatchedCharException.hpp"
#include "String.hpp"

ANTLR_BEGIN_NAMESPACE(antlr)

MismatchedCharException::MismatchedCharException()
: RecognitionException("Mismatched char")
{}

// Expected range / not range
MismatchedCharException::MismatchedCharException(
	int c,
	int lower,
	int upper_,
	bool matchNot,
	CharScanner* scanner_
) : RecognitionException("Mismatched char")
  , foundChar(c)
  , expecting(lower)
  , upper(upper_)
{
	// get instantaneous values of file/line/column
	scanner = scanner_;
	line = scanner->getLine();
	fileName = scanner->getFilename();
	column = scanner->getColumn();
	mismatchType = matchNot ? NOT_RANGE : RANGE;
}


// Expected token / not token
MismatchedCharException::MismatchedCharException(
	int c,
	int expecting_,
	bool matchNot,
	CharScanner* scanner_
) : RecognitionException("Mismatched char")
  , foundChar(c)
  , expecting(expecting_)
{
	// get instantaneous values of file/line/column
	scanner = scanner_;
	line = scanner->getLine();
	fileName = scanner->getFilename();
	column = scanner->getColumn();
	mismatchType = matchNot ? NOT_CHAR : CHAR;
}

// Expected BitSet / not BitSet
MismatchedCharException::MismatchedCharException(
	int c,
	BitSet set_,
	bool matchNot,
	CharScanner* scanner_
) : RecognitionException("Mismatched char")
  , foundChar(c)
  , set(set_)
{
	// get instantaneous values of file/line/column
	scanner = scanner_;
	line = scanner->getLine();
	fileName = scanner->getFilename();
	column = scanner->getColumn();
	mismatchType = matchNot ? NOT_SET : SET;
}

MismatchedCharException::MismatchedCharException(
	const ANTLR_USE_NAMESPACE(std)string& s,
	int line
) : RecognitionException(s)
{
}

/**
 * Returns the error message that happened on the line/col given.
 * Copied from toString().
 */
ANTLR_USE_NAMESPACE(std)string MismatchedCharException::getMessage() const
{
	ANTLR_USE_NAMESPACE(std)string s;

	switch (mismatchType) {
	case CHAR :
		s += "expecting '" + charName(expecting) + "', found '" + charName(foundChar) + "'";
		break;
	case NOT_CHAR :
		s += "expecting anything but '" + charName(expecting) + "'; got it anyway";
		break;
	case RANGE :
		s += "expecting token in range: '" + charName(expecting) + "'..'" + charName(upper) + "', found '" + charName(foundChar) + "'";
		break;
	case NOT_RANGE :
		s += "expecting token NOT in range: " + charName(expecting) + "'..'" + charName(upper) + "', found '" + charName(foundChar) + "'";
		break;
	case SET :
	case NOT_SET :
		{
			s += ANTLR_USE_NAMESPACE(std)string("expecting ") + (mismatchType == NOT_SET ? "NOT " : "") + "one of (";
			ANTLR_USE_NAMESPACE(std)vector<int> elems = set.toArray();
			for (int i = 0; i < (int) elems.size(); i++) {
				s += " '";
				s += charName(elems[i]);
				s += "'";
			}
			s += "), found '" + charName(foundChar) + "'";
		}
		break;
	default :
		s += RecognitionException::getMessage();
		break;
	}

	return s;
}

ANTLR_END_NAMESPACE

