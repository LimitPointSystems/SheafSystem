
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

/// @file
/// Interface for class field_jcb_ed.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_ED_H
#define COM_LIMITPOINT_FIELDS_FIELD_JCB_ED_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_H
#include "ComLimitPoint/fields/field_jcb.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_jcb_ed;
class SHEAF_DLL_SPEC jcb_ed;
class SHEAF_DLL_SPEC jcb_ed_lite;
}

namespace fields
{

///
/// A property of type sec_jcb_ed as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_jcb_ed : public field_jcb
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_JCB_ED
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_jcb_ed property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_jcb_ed();

  ///
  /// Copy constructor.
  ///
  field_jcb_ed(const field_jcb_ed& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_jcb_ed(const sec_ed& xcoordinates, const sec_jcb_ed& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_jcb_ed(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_jcb_ed& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_jcb_ed& operator=(const field_jcb_ed& xother);

  ///
  /// Assignment operator.
  ///
  field_jcb_ed& operator=(const sec_jcb_ed& xsection);

  ///
  /// Assignment operator.
  ///
  field_jcb_ed& operator=(const jcb_ed& xfiber);

  ///
  /// Assignment operator.
  ///
  field_jcb_ed& operator=(const jcb_ed_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_jcb_ed();

  ///
  /// The dependent variable of this field.
  ///
  sec_jcb_ed& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_jcb_ed& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_jcb_ed(sec_jcb_ed* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_JCB_ED
  //===========================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// Conformance test; true if xother conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual field_jcb_ed* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_JCB_ED
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC field_jcb_ed& operator>>(const field_jcb_ed& xsrc, field_jcb_ed& xdst);

///
/// Inserts field_jcb_ed xfield into ostream xos.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream& xos, const field_jcb_ed& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

//...


#endif // ifndef COM_LIMITPOINT_FIELDS_FIELD_JCB_ED_H
