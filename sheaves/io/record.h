
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

// Interface for class record

#ifndef RECORD_H
#define RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POSET_SCAFFOLD_H
#include "poset_scaffold.h"
#endif

#include "record_index.h"

namespace sheaf 
{

class data_type_map;
class poset_data_type_map;
  
///
/// The general variable length record wrapper/adapter for transferring
/// data between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC record : public any
{
public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  record(const record& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual record* clone() const;

  ///
  /// Destructor
  ///
  virtual ~record();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // RECORD INTERFACE

  ///
  /// Creates an instance with type map xtype_map
  ///
  record(const poset_scaffold& xscaffold);

  

  ///
  /// The external index of this record.
  ///
  inline record_index external_index() const
  {
    return _index;
  };

  ///
  /// Sets the index of this record to xindex
  ///
  inline void put_external_index(const record_index& xindex)
  {
    _index = xindex;
  };

  

  ///
  /// The scaffold for the poset associated with this record (mutable version).
  ///
  inline poset_scaffold& scaffold()
  {
    return _scaffold;
  };

  ///
  /// The scaffold for the poset associated with this record (const version).
  ///
  inline const poset_scaffold& scaffold() const
  {
    return _scaffold;
  };

  

  ///
  /// The data type map used to convert data for this record (mutable version).
  ///
  inline poset_data_type_map& type_map()
  {
    return scaffold().type_map();
  };

  ///
  /// The data type map used to convert data for this record (const version).
  ///
  inline const poset_data_type_map& type_map() const
  {
    return scaffold().type_map();
  };

protected:

  // Default constructor.
  // Default construction prohibited because scaffold must be initialized
  //  inline record() {} ;


private:

  // The external index of this record.

  record_index _index;

  // The scaffold for the poset associated with this record.

  poset_scaffold& _scaffold;

};

} // namespace sheaf

#endif // ifndef RECORD_H







