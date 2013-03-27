
// $RCSfile: field_met_ed.h,v $ $Revision: 1.15 $ $Date: 2013/03/21 17:40:19 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_met_ed.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_MET_ED_H
#define FIELD_MET_ED_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_MET_H
#include "field_met.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_met_ed;
class SHEAF_DLL_SPEC met_ed;
class SHEAF_DLL_SPEC met_ed_lite;
}

namespace fields
{

///
/// A property of type sec_met_ed as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_met_ed : public field_met
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_MET_ED
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_met_ed property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_met_ed();

  ///
  /// Copy constructor.
  ///
  field_met_ed(const field_met_ed& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_met_ed(const sec_ed& xcoordinates, const sec_met_ed& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_met_ed(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_met_ed& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_met_ed& operator=(const field_met_ed& xother);

  ///
  /// Assignment operator.
  ///
  field_met_ed& operator=(const sec_met_ed& xsection);

  ///
  /// Assignment operator.
  ///
  field_met_ed& operator=(const met_ed& xfiber);

  ///
  /// Assignment operator.
  ///
  field_met_ed& operator=(const met_ed_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_met_ed();

  ///
  /// The dependent variable of this field.
  ///
  sec_met_ed& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_met_ed& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_met_ed(sec_met_ed* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_MET_ED
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
  virtual field_met_ed* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_MET_ED
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_met_ed& operator>>(const field_met_ed& xsrc, field_met_ed& xdst);

///
/// Inserts field_met_ed xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_met_ed& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

//...


#endif // ifndef FIELD_MET_ED_H
