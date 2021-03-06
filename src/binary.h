/*
 *  Copyright 2001-2014 Adrian Thurston <thurston@complang.org>
 */

/*  This file is part of Ragel.
 *
 *  Ragel is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  Ragel is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with Ragel; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef _C_BINARY_H
#define _C_BINARY_H

#include <iostream>
#include "codegen.h"

/* Forwards. */
struct CodeGenData;
struct NameInst;
struct RedTransAp;
struct RedStateAp;

class Binary
	: public CodeGen
{
public:
	Binary( const CodeGenArgs &args );

private:
	void taIndicies();
	void taTransCondSpacesWi();
	void taTransOffsetsWi();
	void taTransLengthsWi();
	void taTransCondSpaces();
	void taTransOffsets();
	void taTransLengths();
	void taEofTransDirect();
	void taEofTransIndexed();

protected:
	TableArray keyOffsets;
	TableArray singleLens;
	TableArray rangeLens;
	TableArray indexOffsets;
	TableArray indicies;
#if 0
	TableArray transCondSpacesWi;
	TableArray transOffsetsWi;
	TableArray transLengthsWi;
#endif
	TableArray transCondSpaces;
	TableArray transOffsets;
	TableArray transLengths;
	TableArray condTargs;
	TableArray condActions;
	TableArray eofTransDirect;
	TableArray eofTransIndexed;
	TableArray keys;
	TableArray condKeys;

	std::ostream &COND_KEYS_v1();
	std::ostream &COND_SPACES_v1();
	std::ostream &INDICIES();
	std::ostream &INDEX_OFFSETS();
	std::ostream &SINGLE_LENS();
	std::ostream &RANGE_LENS();
#if 0
	std::ostream &TRANS_TARGS_WI();
#endif
	std::ostream &ACTIONS_ARRAY();

	void taKeyOffsets();
	void taSingleLens();
	void taRangeLens();
	void taIndexOffsets();
	void taIndiciesAndTrans();
	void taCondTargs();
	void taCondActions();
	void taToStateActions();
	void taFromStateActions();
	void taEofActions();
	void taEofTrans();
	void taKeys();
	void taActions();
	void taCondKeys();
	void taNfaTargs();
	void taNfaOffsets();
	void taNfaPushActions();
	void taNfaPopTrans();

	void calcIndexSize();
	void setKeyType();
	virtual void tableDataPass();
	void genAnalysis();

	void LOCATE_TRANS();
	void LOCATE_COND();

	void GOTO( ostream &ret, int gotoDest, bool inFinish );
	void CALL( ostream &ret, int callDest, int targState, bool inFinish );
	void NCALL( ostream &ret, int callDest, int targState, bool inFinish );
	void NEXT( ostream &ret, int nextDest, bool inFinish );
	void GOTO_EXPR( ostream &ret, GenInlineItem *ilItem, bool inFinish );
	void NEXT_EXPR( ostream &ret, GenInlineItem *ilItem, bool inFinish );
	void CALL_EXPR( ostream &ret, GenInlineItem *ilItem, int targState, bool inFinish );
	void NCALL_EXPR( ostream &ret, GenInlineItem *ilItem, int targState, bool inFinish );
	void CURS( ostream &ret, bool inFinish );
	void TARGS( ostream &ret, bool inFinish, int targState );
	void RET( ostream &ret, bool inFinish );
	void NRET( ostream &ret, bool inFinish );
	void BREAK( ostream &ret, int targState, bool csForced );
	void NBREAK( ostream &ret, int targState, bool csForced );

	virtual void TO_STATE_ACTION( RedStateAp *state ) = 0;
	virtual void FROM_STATE_ACTION( RedStateAp *state ) = 0;
	virtual void EOF_ACTION( RedStateAp *state ) = 0;
	virtual void COND_ACTION( RedCondPair *cond ) = 0;

	virtual void NFA_PUSH_ACTION( RedNfaTarg *targ ) = 0;
	virtual void NFA_POP_TEST( RedNfaTarg *targ ) = 0;

	void NFA_PUSH();
	void NFA_POP();
};

#endif
