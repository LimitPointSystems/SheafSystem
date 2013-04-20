

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_tp.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_TP_H
#define FIELD_TP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_VD_H
#include "field_vd.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_tp;
class SHEAF_DLL_SPEC tp;
class SHEAF_DLL_SPEC tp_lite;
}

namespace fields
{

///
/// A property of type sec_tp as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_tp : public field_vd
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_TP
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_tp property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_tp();

  ///
  /// Copy constructor.
  ///
  field_tp(const field_tp& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_tp(const sec_ed& xcoordinates, const sec_tp& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_tp(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_tp& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_tp& operator=(const field_tp& xother);

  ///
  /// Assignment operator.
  ///
  field_tp& operator=(const sec_tp& xsection);

  ///
  /// Assignment operator.
  ///
  field_tp& operator=(const tp& xfiber);

  ///
  /// Assignment operator.
  ///
  field_tp& operator=(const tp_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_tp();

  ///
  /// The dependent variable of this field.
  ///
  sec_tp& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_tp& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_tp(sec_tp* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_TP
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
  virtual field_tp* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_TP
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_tp& operator>>(const field_tp& xsrc, field_tp& xdst);

///
/// Inserts field_tp xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_tp& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

#include "field_tp_funcs.h"


#endif // ifndef FIELD_TP_H
