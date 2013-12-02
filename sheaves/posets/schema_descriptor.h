
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

// Interface for class schema_descriptor

#ifndef SCHEMA_DESCRIPTOR_H
#define SCHEMA_DESCRIPTOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{
  
///
/// A description of a dof in a schema.
///
class SHEAF_DLL_SPEC schema_descriptor : public any
{

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual schema_descriptor* clone() const;

  // Assignment operator provided by compiler.

  ///
  /// Equality operator.
  ///
  bool operator==(const schema_descriptor& xother) const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // SCHEMA_DESCRIPTOR FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  ///
  schema_descriptor();

  ///
  /// Copy constructor
  ///
  ///
  schema_descriptor(const schema_descriptor& xother);

  ///
  /// Creates an instance with name == xname,
  /// type == xtype, and is_table_dof == xis_table_dof.
  ///
  schema_descriptor(const std::string& xname,
                    primitive_type xtype = NOT_A_PRIMITIVE_TYPE,
                    bool xis_table_dof = true);

  ///
  /// Destructor
  ///
  virtual ~schema_descriptor();

  ///
  /// The name of the dof described by this.
  ///
  string name;

  ///
  /// The type of the dof described by this.
  ///
  primitive_type type;

  ///
  /// The role of the dof described by this;
  /// true if this describes a table dof.
  ///
  bool is_table_dof;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================


///
/// Insert schema_descriptor xsd into ostream& os.
///
SHEAF_DLL_SPEC
std::ostream & operator << (std::ostream& os, const schema_descriptor& xsd);


///
/// Extract schema_descriptor xsd from istream& is.
///
SHEAF_DLL_SPEC
std::istream & operator >> (std::istream& is, schema_descriptor& xsd);

///
/// The deep size of the referenced object of type schema_descriptor.
/// if xinclude_shallow, add the sizeof xsd to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const schema_descriptor& xsd, bool xinclude_shallow = true);

 
} // namespace sheaf

#endif // ifndef SCHEMA_DESCRIPTOR_H
