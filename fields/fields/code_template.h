
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class ${derived}.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#ifndef ${DERIVED}_H
#define ${DERIVED}_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ${BASE}_H
#include "${base}.h"
#endif

namespace fiber_bundle
{
class SHEAF_DLL_SPEC ${coords};
class SHEAF_DLL_SPEC ${property};
class SHEAF_DLL_SPEC ${fiber};
class SHEAF_DLL_SPEC ${volatile_fiber};
}

namespace fields
{

///
/// A property of type ${property} as a function of global coordinates.
///
class SHEAF_DLL_SPEC ${derived} : public ${base}
{
  //===========================================================================
  /// @name ${ABS_BASE} FACET OF CLASS ${DERIVED}
  //===========================================================================
  //@{
public:

  /// Typedefs:

  /// The property section type.
  ///
  typedef ${property} property_section_type;

  ///
  /// The coordinates section type.
  ///
  typedef ${coords} coordinates_section_type;

  ///
  /// Default constructor.
  ///
  ${derived}();

  ///
  /// Copy constructor.
  ///
  ${derived}(const ${derived}& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  ${derived}(const ${coords}& xcoordinates, const ${property}& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  ${derived}(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Assignment operator.
  ///
  virtual ${derived}& operator=(const ${abs_base}& xother);

  ///
  /// Assignment operator.
  ///
  ${derived}& operator=(const ${derived}& xother);

  ///
  /// Assignment operator.
  ///
  ${derived}& operator=(const ${property}& xsection);

  ///
  /// Assignment operator.
  ///
  ${derived}& operator=(const ${fiber}& xfiber);

  ///
  /// Assignment operator.
  ///
  ${derived}& operator=(const ${volatile_fiber}& xfiber);

  ///
  /// Destructor.
  ///
  virtual ~${derived}();

  ///
  /// The dependent variable of this field.
  ///
  ${property}& property() const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const ${derived}& xother,
                                  bool xauto_access) const;

protected:

  ///
  /// Covariant constructor.
  ///
  ${derived}(${property}* xproperty,
         ${coords_invertible}* xcoordinates,
         base_space_member* xbase_space);

private:

  //@}

  //===========================================================================
  /// @name ANY FACET OF CLASS ${DERIVED}
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
  virtual ${derived}* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS ${DERIVED}
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
${derived}& operator>>(const ${derived}& xsrc, ${derived}& xdst);

///
/// Inserts ${derived} xfield into ostream xos.
///
ostream& operator<<(ostream& xos, const ${derived}& xfield);

} // namespace fields

//==============================================================================

/// Include field_vd algebra function declarations.

${PLACEHOLDER}


#endif // ifndef ${DERIVED}_H
