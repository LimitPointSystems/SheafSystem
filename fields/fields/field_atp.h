

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_atp.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_ATP_H
#define FIELD_ATP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_TP_H
#include "field_tp.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_atp;
class SHEAF_DLL_SPEC atp;
class SHEAF_DLL_SPEC atp_lite;
}

namespace fields
{

///
/// A property of type sec_atp as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_atp : public field_tp
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_ATP
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_atp property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_atp();

  ///
  /// Copy constructor.
  ///
  field_atp(const field_atp& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_atp(const sec_ed& xcoordinates, const sec_atp& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_atp(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_atp& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_atp& operator=(const field_atp& xother);

  ///
  /// Assignment operator.
  ///
  field_atp& operator=(const sec_atp& xsection);

  ///
  /// Assignment operator.
  ///
  field_atp& operator=(const atp& xfiber);

  ///
  /// Assignment operator.
  ///
  field_atp& operator=(const atp_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_atp();

  ///
  /// The dependent variable of this field.
  ///
  sec_atp& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_atp& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_atp(sec_atp* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_ATP
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
  virtual field_atp* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_ATP
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_atp& operator>>(const field_atp& xsrc, field_atp& xdst);

///
/// Inserts field_atp xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_atp& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

#include "field_atp_funcs.h"


#endif // ifndef FIELD_ATP_H