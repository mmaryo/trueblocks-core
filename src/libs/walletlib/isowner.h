#pragma once
/*-------------------------------------------------------------------------------------------
 * QuickBlocks - Decentralized, useful, and detailed data from Ethereum blockchains
 * Copyright (c) 2018 Great Hill Corporation (http://quickblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "transaction.h"

//--------------------------------------------------------------------------
class QIsOwner;
typedef SFArrayBase<QIsOwner>         QIsOwnerArray;
typedef SFList<QIsOwner*>             QIsOwnerList;

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class QIsOwner : public CTransaction {
public:
    SFAddress _addr;

public:
    QIsOwner(void);
    QIsOwner(const QIsOwner& is);
    virtual ~QIsOwner(void);
    QIsOwner& operator=(const QIsOwner& is);

    DECLARE_NODE(QIsOwner);

    // EXISTING_CODE
    // EXISTING_CODE
    friend ostream& operator<<(ostream& os, const QIsOwner& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const QIsOwner& is);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline QIsOwner::QIsOwner(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline QIsOwner::QIsOwner(const QIsOwner& is) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(is);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline QIsOwner::~QIsOwner(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void QIsOwner::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void QIsOwner::initialize(void) {
    CTransaction::initialize();

    _addr = "";

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void QIsOwner::duplicate(const QIsOwner& is) {
    clear();
    CTransaction::duplicate(is);

    _addr = is._addr;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline QIsOwner& QIsOwner::operator=(const QIsOwner& is) {
    duplicate(is);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//---------------------------------------------------------------------------
extern SFArchive& operator>>(SFArchive& archive, QIsOwnerArray& array);
extern SFArchive& operator<<(SFArchive& archive, const QIsOwnerArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
