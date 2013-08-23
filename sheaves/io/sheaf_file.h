
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

// Interface for class sheaf_file

#ifndef SHEAF_FILE_H
#define SHEAF_FILE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef STD_HDF5_H
#include "std_hdf5.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class data_type_map;
class dof_tuple_record_set;
class member_record_set;
  
///
/// An encapsulation of an HDF file containing sheaf data
///
class SHEAF_DLL_SPEC sheaf_file : public any
{

  friend class data_type_map;
  friend class record_set;
  friend class attributes_record_set;
  friend class member_record_set;
  friend class dof_tuple_record_set;

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor
  ///
  ///
  sheaf_file();

  ///
  /// Copy constructor
  ///
  ///
  sheaf_file(const sheaf_file& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual sheaf_file* clone() const;

  ///
  /// Destructor
  ///
  virtual ~sheaf_file();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // SHEAF_FILE INTERFACE

  

  ///
  /// The name of this file.
  ///
  inline string name() const
  {
    return _name;
  } ;

  ///
  /// File access modes
  ///
  enum access_mode {NONE, READ_ONLY, READ_WRITE};

  ///
  /// Opens a file with name xname, with access mode xmode.
  /// If xclobber and the file already exists, delete it first.
  ///
  void open(const string &xname, access_mode xmode = READ_WRITE, bool xclobber = true);

  ///
  /// True if this file is open.
  ///
  bool is_open() const;

  ///
  /// The current access mode.
  ///
  access_mode mode() const;

  ///
  /// Closes the file.
  ///
  void close();

  ///
  /// Data type map for primitive types in this file (mutable version)
  ///
  data_type_map& type_map();

  ///
  /// Data type map for primitive types in this file (const version)
  ///
  const data_type_map& type_map() const;

  ///
  /// True if type map previously defined.
  ///
  bool type_map_defined() const;


private:

  ///
  /// The name of this file.
  ///
  string _name;

  ///
  /// A handle for the underlying HDF file
  ///
  hid_t _hdf_id;

  ///
  /// A handle for the underlying HDF file
  ///
  hid_t hdf_id() const;

  ///
  /// The current access mode.
  ///
  access_mode _mode;

  ///
  /// Data type map for primitive types in this file
  ///
  data_type_map* _type_map;

};

} // namespace sheaf

#endif // ifndef SHEAF_FILE_H







