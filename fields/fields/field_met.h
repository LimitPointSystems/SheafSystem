

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class field_met.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef FIELD_MET_H
#define FIELD_MET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_ST2_H
#include "field_st2.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_met;
class SHEAF_DLL_SPEC met;
class SHEAF_DLL_SPEC met_lite;
}

namespace fields
{

///
/// A property of type sec_met as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_met : public field_st2
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_MET
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef sec_met property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef sec_ed coordinates_section_type;

  ///
  /// Default constructor.
  ///
  field_met();

  ///
  /// Copy constructor.
  ///
  field_met(const field_met& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_met(const sec_ed& xcoordinates, const sec_met& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_met(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual field_met& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_met& operator=(const field_met& xother);

  ///
  /// Assignment operator.
  ///
  field_met& operator=(const sec_met& xsection);

  ///
  /// Assignment operator.
  ///
  field_met& operator=(const met& xfiber);

  ///
  /// Assignment operator.
  ///
  field_met& operator=(const met_lite& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~field_met();

  ///
  /// The dependent variable of this field.
  ///
  sec_met& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_met& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  field_met(sec_met* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS FIELD_MET
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
  virtual field_met* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_MET
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_met& operator>>(const field_met& xsrc, field_met& xdst);

///
/// Inserts field_met xfield into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const field_met& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

#include "field_met_funcs.h"


#endif // ifndef FIELD_MET_H
