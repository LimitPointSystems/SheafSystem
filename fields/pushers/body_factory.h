
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

/// @file
/// Interface for class body_factory

#ifndef BODY_FACTORY_H
#define BODY_FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
template <class T>
class block;
}

namespace fiber_bundle
{
class fiber_bundles_namespace;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle; 

class field_vd;

///
/// Test case generator for classes body_builder and body_pusher.
///
class SHEAF_DLL_SPEC body_factory
{

  // ===========================================================
  /// @name BODY_FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Uses body_builder to create bodies in a 1D unstructured mesh.
  ///
  static field_vd* new_1d_unstructured_bodies(fiber_bundles_namespace& xns,
      const string& xname_prefix);

  ///
  /// Uses body_builder to create bodies in a 1D uniform mesh.
  ///
  static field_vd* new_1d_uniform_bodies(fiber_bundles_namespace& xns,
                                         const string& xname_prefix);

  ///
  /// Uses body_builder to create bodies in a 2D unstructured mesh.
  ///
  static field_vd* new_2d_unstructured_bodies(fiber_bundles_namespace& xns,
      const string& xname_prefix);

  ///
  /// Uses body_builder to create bodies in a 2D uniform mesh.
  ///
  static field_vd* new_2d_uniform_bodies(fiber_bundles_namespace& xns,
                                         const string& xname_prefix);

  ///
  /// Uses body_builder to create bodies in a 3D unstructured mesh.
  ///
  static field_vd* new_3d_unstructured_bodies(fiber_bundles_namespace& xns,
      const string& xname_prefix);

  ///
  /// Uses body_builder to create bodies in a 3D uniform mesh.
  ///
  static field_vd* new_3d_uniform_bodies(fiber_bundles_namespace& xns,
                                         const string& xname_prefix);

private:

  ///
  /// Sets xproperty_value[0] == sqrt(x*x + y*y);
  /// results in one circular body when fed to body_builder.
  ///
  static void one_body(block<sec_vd_value_type>& xglobal_coords,
                       block<sec_vd_dof_type>& xproperty_value);


  ///
  /// Sets xproperty_value[0] == 1 if |x| >= .5 and |y| and |z| <= .5, 0 otherwise;
  /// results in 2 square bodies when fed to body_builder.
  ///
  static void two_bodies(block<sec_vd_value_type>& xglobal_coords,
                         block<sec_vd_dof_type>& xproperty_value);


  ///
  /// Extracts a bodies from a scalar field defining one circular body.
  ///
  static void build_circular_body(field_vd& xfield);

  ///
  /// Extracts a bodies from a scalar field defining 2 square bodies.
  ///
  static void build_square_bodies(field_vd& xfield);


  ///
  /// Extracts one circular and two square bodies and outputs the base space.
  ///
  static void build_bodies(field_vd& xfield);

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef BODY_FACTORY_H
