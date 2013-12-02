
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Implementation for class error_message.

#include "error_message.h"

#include "assert_contract.h"
#include "std_iostream.h"
#include "std_strstream.h"
#include "std_stdexcept.h"


// ===========================================================
// ERROR_MESSAGE FACET
// ===========================================================

///
sheaf::error_message::
error_message()
{

  // Preconditions:


  // Body:

  // Source is empty.
  // Text is empty

  _level = INFORMATION;

  // Postconditions:

  //   ensure(invariant());
  ensure(source() == "");
  ensure(text() == "");
  ensure(level() == INFORMATION);

  // Exit:

  return;
}


///
sheaf::error_message::
error_message(const error_message& xother)
{

  // Preconditions:


  // Body:

  *this = xother;

  // Postconditions:

  //   ensure(invariant());
  ensure(text() == xother.text());
  ensure(level() == xother.level());

  // Exit:

  return;
}

sheaf::error_message&
sheaf::error_message:: 
operator=(const error_message& xother)
{
  // Preconditions:

  // Body:

  if(this != &xother)
  {
    _source = xother.source();
    _text = xother.text();
    _level = xother.level(); 
  }

  // Postconditions:

  //ensure(invariant());
  ensure(source() == xother.source());
  ensure(text() == xother.text());
  ensure(level() == xother.level());

  // Exit:

  return *this;
}

///
sheaf::error_message::
~error_message()
{

  // Preconditions:


  // Body:

  // No action required

  // Postconditions:

  //   ensure(invariant());

  // Exit:

  return;
}

///
sheaf::error_message::
error_message(level_type xlevel, const std::string& xsource, const std::string& xtext)
{

  // Preconditions:

  require(xlevel != LEVEL_TYPE_UB);
  require(!xsource.empty());
  require(!xtext.empty());

  // Body:

  _level = xlevel;
  _source = xsource;
  _text = xtext;

  // Postconditions:

  //   ensure(invariant());
  ensure(level() == xlevel);
  ensure(source() == xsource);
  ensure(text() == xtext);

  // Exit:

  return;
}

///
sheaf::error_message::
error_message(level_type xlevel, const std::string& xfile, int xline, const std::string& xtext)
{

  // Preconditions:

  require(xlevel != LEVEL_TYPE_UB);
  require(!xfile.empty());
  //  require(!xtext.empty());

  // Body:

  _level = xlevel;
  _source = xfile;
  strstream lstrm;
  lstrm << xline;
  string lline;
  lstrm >> lline;
  _source += " at line ";
  _source += lline;
  _text = xtext;

  // Postconditions:

  //   ensure(invariant());
  ensure(level() == xlevel);
  ensure(text() == xtext);

  // Exit:

  return;
}


///
std::string
sheaf::error_message::
source() const
{
  return _source;
}

///
std::string
sheaf::error_message::
text() const
{
  return _text;
}

///
sheaf::error_message::level_type
sheaf::error_message::
level() const
{
  return _level;
}

///
void
sheaf::error_message::
post(bool xforce_exit) const
{
  // Preconditions:


  // Body:

  /// @hack just print the message and
  /// quit if the error is severe enough.

  cerr << level_name(_level) << ": "
  << "In " << _source << ": "
  << _text
  << endl;

  if(xforce_exit)
  {
    //exit(_level);
    throw std::logic_error(level_name(_level));
  }

  // Postconditions:


  // Exit:

  return;
}

///
const std::string&
sheaf::error_message::
level_name(level_type xlevel )
{
  // Preconditions:

  require((0 <= xlevel ) && (xlevel < LEVEL_TYPE_UB));

  // Body:

  static const string names[LEVEL_TYPE_UB] =
    {
      "UNSPECIFIED",
      "INFORMATION",
      "WARNING",
      "SEVERE ERROR",
      "FATAL ERROR"
    };

  const string& result = names[xlevel];

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

///
std::ostream&
sheaf::operator<<(std::ostream& xos, const error_message& xmsg)
{
  // Preconditions:


  // Body:

  if(xmsg.level() != error_message::UNSPECIFIED)
  {
    xos << error_message::level_name(xmsg.level()) << ": ";
  }

  xos << "In " << xmsg.source() << ": " << xmsg.text();

  // Postconditions:


  // Exit:

  return xos;
}
