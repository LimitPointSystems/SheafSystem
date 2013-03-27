
// $RCSfile: field_st3.h,v $ $Revision: 1.15 $ $Date: 2013/03/21 17:40:19 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_st3.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_ST3_H
#define FIELD_ST3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_STP_H
#include "field_stp.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_st3;
class SHEAF_DLL_SPEC st3;
class SHEAF_DLL_SPEC st3_lite;
}

namespace fields
{

///
/// A property of type sec_st3 as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_st3 : public field_stp
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_ST3
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_st3 property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_st3();

  ///
  /// Copy constructor.
  ///
  field_st3(const field_st3& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_st3(const sec_ed& xcoordinates, const sec_st3& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_st3(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_st3& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_st3& operator=(const field_st3& xother);

  ///
  /// Assignment operator.
  ///
  field_st3& operator=(const sec_st3& xsection);

  ///
  /// Assignment operator.
  ///
  field_st3& operator=(const st3& xfiber);

  ///
  /// Assignment operator.
  ///
  field_st3& operator=(const st3_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_st3();

  ///
  /// The dependent variable of this field.
  ///
  sec_st3& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_st3& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_st3(sec_st3* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_ST3
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
  virtual field_st3* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_ST3
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_st3& operator>>(const field_st3& xsrc, field_st3& xdst);

///
/// Inserts field_st3 xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_st3& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

//...


#endif // ifndef FIELD_ST3_H
