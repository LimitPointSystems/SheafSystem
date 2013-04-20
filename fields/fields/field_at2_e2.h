

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_at2_e2.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_AT2_E2_H
#define FIELD_AT2_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_AT2_H
#include "field_at2.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_at2_e2;
class SHEAF_DLL_SPEC at2_e2;
class SHEAF_DLL_SPEC at2_e2_lite;
}

namespace fields
{

///
/// A property of type sec_at2_e2 as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_at2_e2 : public field_at2
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_AT2_E2
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_at2_e2 property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_at2_e2();

  ///
  /// Copy constructor.
  ///
  field_at2_e2(const field_at2_e2& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_at2_e2(const sec_ed& xcoordinates, const sec_at2_e2& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_at2_e2(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_at2_e2& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_at2_e2& operator=(const field_at2_e2& xother);

  ///
  /// Assignment operator.
  ///
  field_at2_e2& operator=(const sec_at2_e2& xsection);

  ///
  /// Assignment operator.
  ///
  field_at2_e2& operator=(const at2_e2& xfiber);

  ///
  /// Assignment operator.
  ///
  field_at2_e2& operator=(const at2_e2_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_at2_e2();

  ///
  /// The dependent variable of this field.
  ///
  sec_at2_e2& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_at2_e2& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_at2_e2(sec_at2_e2* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_AT2_E2
  //===========================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  ///
  /// Conformance test; true if xother conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual field_at2_e2* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_AT2_E2
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_at2_e2& operator>>(const field_at2_e2& xsrc, field_at2_e2& xdst);

///
/// Inserts field_at2_e2 xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_at2_e2& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

//...


#endif // ifndef FIELD_AT2_E2_H