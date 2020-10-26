// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_STATEMENT_H_
#define _GSC_STATEMENT_H_

/*namespace gsc
{*/

struct statement
{
	std::uint32_t index;
	std::string data;

	statement() : index(0) { }
};

/*} // namespace gsc*/

#endif // _GSC_STATEMENT_H_
