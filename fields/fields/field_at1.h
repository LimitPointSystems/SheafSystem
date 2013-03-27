
// $RCSfile: field_at1.h,v $ $Revision: 1.15 $ $Date: 2013/03/21 17:40:18 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_at1.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_AT1_H
#define FIELD_AT1_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_ATP_H
#include "field_atp.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_at1;
class SHEAF_DLL_SPEC at1;
class SHEAF_DLL_SPEC at1_lite;
}

namespace fields
{

///
/// A property of type sec_at1 as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_at1 : public field_atp
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_AT1
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_at1 property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_at1();

  ///
  /// Copy constructor.
  ///
  field_at1(const field_at1& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_at1(const sec_ed& xcoordinates, const sec_at1& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_at1(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_at1& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_at1& operator=(const field_at1& xother);

  ///
  /// Assignment operator.
  ///
  field_at1& operator=(const sec_at1& xsection);

  ///
  /// Assignment operator.
  ///
  field_at1& operator=(const at1& xfiber);

  ///
  /// Assignment operator.
  ///
  field_at1& operator=(const at1_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_at1();

  ///
  /// The dependent variable of this field.
  ///
  sec_at1& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_at1& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_at1(sec_at1* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_AT1
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
  virtual field_at1* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_AT1
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_at1& operator>>(const field_at1& xsrc, field_at1& xdst);

///
/// Inserts field_at1 xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_at1& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

//...


#endif // ifndef FIELD_AT1_H
