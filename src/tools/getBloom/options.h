#pragma once
/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2018 Great Hill Corporation (http://greathill.com)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include "etherlib.h"
#include "bloom_blocks.h"
//-----------------------------------------------------------------------------
class COptions : public CBlockOptions {
public:
    bool force;
    bool isRaw;
    bool blockOnly;
    bool receiptsOnly;
    bool asBits;
    bool asBars;
    bool bitCounts;

    COptions(void);
    ~COptions(void);

    string_q postProcess(const string_q& which, const string_q& str) const override;
    bool parseArguments(string_q& command) override;
    void Init(void) override;
    bool isMulti(void) const;
};

//-----------------------------------------------------------------------------
extern size_t foundFile(const string_q& path, void *data);
