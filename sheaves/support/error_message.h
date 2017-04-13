
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

// Interface for class error_message.

#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef STD_STRING_H
#include "SheafSystem/std_string.h"
#endif

namespace sheaf
{
  
///
/// A message to report error conditions.
///
class SHEAF_DLL_SPEC error_message
{

public:

  // ===========================================================
  // ERROR_MESSAGE FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  error_message();

  ///
  /// Copy constructor
  ///
  error_message(const error_message& xother);

  ///
  /// Assignment operator
  ///
  error_message& operator=(const error_message& xother);

  ///
  /// Destructor
  ///
  virtual ~error_message();

  ///
  /// The set of predefined error levels.
  ///
  enum level_type
  {
    UNSPECIFIED = 0,
    INFORMATION,
    WARNING,
    SEVERE_ERROR,
    FATAL_ERROR,
    LEVEL_TYPE_UB // Must be last.
  };

  ///
  /// Creates an instance with level xlevel, source xsource, and text xtext.
  ///
  error_message(level_type xlevel, const std::string& xsource, const std::string& xtext);

  ///
  /// Creates an instance with level xlevel, source file xfile,
  /// source line number xline, and text xtext.
  ///
  error_message(level_type xlevel,
                const std::string& xfile,
                int xline,
                const std::string& xtext);

  ///
  /// The source of this message.
  ///
  std::string source() const;

  ///
  /// The text of this message.
  ///
  std::string text() const;

  ///
  /// The level of this message.
  ///
  level_type level() const;

  ///
  /// Registers this message with the message handling subsystem.
  ///
  void post(bool xforce_exit = false) const;

  ///
  /// The name of level xlevel.
  ///
  static const std::string& level_name(level_type xlevel);

private:
  ///
  /// The source of this message.
  ///
  std::string _source;

  ///
  /// The text of this message.
  ///
  std::string _text;

  ///
  /// The level of this message.
  ///
  level_type _level;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts error message xmsg into ostream xos.
///
SHEAF_DLL_SPEC
std::ostream & operator << (std::ostream &xos, const error_message& xmsg);

#define SOURCE_CODE_LOCATION \
error_message(error_message::UNSPECIFIED, __FILE__, __LINE__, "")

#define post_information_message(x) \
{error_message msg(error_message::INFORMATION, __FILE__, __LINE__, (x)); msg.post(0);}

#define post_warning_message(x) \
{error_message msg(error_message::WARNING, __FILE__, __LINE__, (x)); msg.post(0);}

#define post_severe_error_message(x) \
{error_message msg(error_message::SEVERE_ERROR, __FILE__, __LINE__, (x)); msg.post(0);}

#define post_fatal_error_message(x) \
{error_message msg(error_message::FATAL_ERROR, __FILE__, __LINE__, (x)); msg.post(1);}

} // namespace sheaf

#endif // ifndef ERROR_MESSAGE_H
