
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
/// Interface for class field_vd

#ifndef FIELD_VD_H
#define FIELD_VD_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "SheafSystem/any.h"
#endif

#ifndef FIELDS_H
#include "SheafSystem/fields.h"
#endif

namespace sheaf
{
class name_multimap;
class namespace_poset;
class poset_path;
class subposet;
}

namespace fiber_bundle
{
class base_space_member;
class sec_ed;
class sec_vd;
class sec_at0;
class vd;
class vd_lite;
}

namespace geometry
{
class sec_ed_invertible;
}

namespace fields
{
class discretization_push_action;
class property_disc_iterator;
class put_property_dofs_action;


///
/// A vd-valued property as a function of global coordinates.
///
class SHEAF_DLL_SPEC field_vd : public any
{
  //===========================================================================
  /// @name FIELD_VD FACET OF CLASS FIELD_VD
  //===========================================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  ///
  field_vd();

  ///
  /// Copy constructor
  ///
  ///
  field_vd(const field_vd& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  field_vd(const sec_ed& xcoordinates, const sec_vd& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  field_vd(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Destructor
  ///
  virtual ~field_vd();

  ///
  /// The dimension of the coordinates (independent variable) space.
  ///
  int dc() const;

  ///
  /// The dimension of the property (dependent variable) space.
  ///
  int dp() const;

  ///
  /// The dimension of the base space.
  ///
  int db() const;

  ///
  /// The namespace this resides in.
  ///
  namespace_poset& name_space() const;

  ///
  /// The independent variable of this field.
  ///
  sec_ed_invertible& coordinates() const;

  ///
  /// The dependent variable of this field.
  ///
  sec_vd& property() const;

  ///
  /// The base space of this field.
  ///
  base_space_member& base_space() const;

  ///
  /// Iterator over property discretiation.
  ///
  property_disc_iterator* new_property_disc_iterator() const;

  ///
  /// The type of the function for computing
  /// the property dofs at given global coordinates.
  ///
  typedef void (*property_dof_function_type)
    (block<sec_vd_value_type>& xglobal_coords,
     block<sec_vd_dof_type>& xproperty_dofs);

  ///
  /// Example property dof function;
  /// property value is x*1000000 + y*1000 + z,
  /// intended to be easy to check field dofs for correctness.
  ///
  static void property_dof_function_example(
    block<sec_vd_value_type>& xglobal_coords,
    block<sec_vd_dof_type>& xproperty_dofs);


  ///
  /// Sets the dofs of property() to values computed by xproperty_dofs_fcn.
  ///
  void put_property_dofs(property_dof_function_type xproperty_dofs_fcn,
                         bool xauto_access);


  ///
  /// Sets the dofs of xproperty to values computed by xproperty_dofs_fcn
  /// using xcoordinates to compute the coordinates at the discretization points.
  ///
  static void put_property_dofs(const sec_vd& xcoordinates,
                                sec_vd& xproperty,
                                property_dof_function_type xproperty_dofs_fcn,
                                bool xauto_access);

  ///
  /// OBSOLETE: Use put_proeprty_dofs(property_dof_function_type, bool).
  /// Sets the dofs of property() to values computed by xproperty_dofs_action.
  ///
  void put_property_dofs(put_property_dofs_action& xproperty_dofs_action,
                         bool xauto_access);

  ///
  /// Sets the dofs of xproperty to values computed by xproperty_dofs_fcn
  /// using xcoordinates to compute the coordinates at the discretization points.
  ///
  static void put_property_dofs(const sec_vd& xcoordinates,
                                sec_vd& xproperty,
                                put_property_dofs_action& xproperty_dofs_action,
                                bool xauto_access);

  ///
  /// Prints the property dofs and coordinates at the property
  /// discretization points. If xproperty_dof_fcn != 0, prints
  /// the result of xproperty_dofs_fcn at each discretization point
  /// and the difference with the actual property dofs.
  /// If xzero_specified, assume the result of xproperty_dofs_fcn
  /// is zero wherever property is zero. Intended to be useful for debugging.
  ///
  void print_property_dofs(std::ostream& xos,
                           property_dof_function_type xproperty_dofs_fcn,
                           const std::string& xtitle_text,
                           bool xzero_specified,
                           bool xauto_access) const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const field_vd& xother,
                                  bool xauto_access) const;

  ///
  /// True if the coordinates and property sections
  /// both use the same evaluation subposet.
  ///
  bool same_evaluation() const;

  ///
  /// True if the coordinates and property sections
  /// both use the same discretization subposet.
  ///
  bool same_discretization() const;

  ///
  /// The value of the property at the given global coordinates.
  ///
  void property_at_coordinates(const vd_lite& xcoord, vd_lite& xprop) const;

  ///
  /// The value of the property at the given global coordinates.
  ///
  void property_at_coordinates(const block<sec_vd_value_type>& xcoord,
                               block<sec_vd_value_type>& xprop) const;

  ///
  /// The value of the property at the given global coordinates.
  ///
  void property_at_coordinates(sec_vd_value_type xcoord_base[],
                               int xcoord_ct,
                               sec_vd_value_type xprop_base[],
                               int xprop_ub) const;

  ///
  /// Creates a decomposition of the base space such that the value
  /// of property() is constant on each member.
  /// @hack This function belongs in sec_at0, but is put here
  /// temporarily to avoid problems merging with branch refactor-8.
  ///
  subposet* embed_property(const std::string& xresult_name,
                           name_multimap& xresult_member_names,
                           bool xauto_access);

  ///
  /// Deletes field xfield and all associated section spaces, section schema spaces,
  /// and base space, if they are no longer being used. If xdelete_coord_fiber
  /// delete the coordinate fiber space, if it is no longer beinbg used, and
  /// similarly for xdelete_prop_fiber.
  ///
  static void delete_field_spaces(field_vd* xfield,
                                  bool xdelete_coord_fiber,
                                  bool xdelete_prop_fiber);

protected:

  ///
  /// Covariant constructor.
  ///
  field_vd(sec_vd* xproperty,
           sec_ed_invertible* xcoordinates,
           base_space_member* xbase_space); 

//private:

  /// @hack _coordinates and _property are pointers rather than values
  /// in order to make the accessor functions above const without fixing
  /// the constness of the entire sheaves and fiber bundles components.

  ///
  /// The dependent variable of this field.
  ///
  sec_vd* _property;

  ///
  /// The independent variable of this field.
  ///
  sec_ed_invertible* _coordinates;

  ///
  /// The base space of this field.
  ///
  base_space_member* _base_space;

private:

  //@}

  //===========================================================================
  /// @name READ_WRITE_MONITOR_HANDLE FACET
  //===========================================================================
  //@{

public:

  /// @issue this class needs the public interface of
  /// read_write_monitor_handle, but it can't inherit it, because,
  /// since it has two state objects, not one, it can't support
  /// the private state_obj() method. Nor are the member function
  /// implementations in read_write_monitor_handle which use
  /// state_obj() valid for this class. What we need is an abstract
  /// class that introduces just the public interface.

  ///
  /// True if access control mechanism is disabled.
  /// Default value is enabled (false) and access is controlled
  /// by the per-thread access control functions.
  /// Disabled (true) is equivalent to having read-write access
  /// at all times, irrespective of any access control requests.
  /// Synonym for read_write_monitor::access_control_disabled().
  ///
  static bool access_control_disabled();

  //   ///
  //   /// Disables access control.
  //   /// Disabled (true) is equivalent to having read-write access
  //   /// at all times, irrespective of any access control requests.
  //   /// Synonym for read_write_monitor::disable_access_control().
  //   /// Should only be invoked once at beginning of a program, before any
  //   /// other SheafSystem calls. Once disabled, access control can not be re-enabled.
  //   ///
  //   static void disable_access_control();

  ///
  /// Enables access control.
  /// Synonym for read_write_monitor::enable_access_control().
  /// Should only be invoked once at beginning of a program, before any
  /// other SheafSystem calls. Once enabled, access control can not be disabled.
  ///
  static void enable_access_control();

  ///
  /// True if this handle has a state associated with it.
  ///
  virtual bool is_attached() const;

  ///
  /// True if this is attached and if the coordinates and property are
  /// accessible for read access but not for write.
  /// False is access control is disabled.
  ///
  bool state_is_read_only_accessible() const;

  ///
  /// True if this is attached and if the coordinates and property are 
  /// not accessible for read only access or
  /// access control is disabled.
  ///
  bool state_is_not_read_only_accessible() const;

  ///
  /// True if this is attached and if the coordinates and property are
  /// accessible for read or access control is disabled.
  ///
  bool state_is_read_accessible() const;

  ///
  /// True if this is attached and if the coordinates and property are
  /// not accessible for read or access control is disabled.
  ///
  bool state_is_not_read_accessible() const;

  ///
  /// True if this is attached and if coordinates(), property() and 
  /// (if xbase access) base_space() are accessible for read and write
  /// or access control is disabled.
  ///
  bool state_is_read_write_accessible(bool xbase_access = false) const;

  ///
  /// True if this is not attached or if coordinates(), property() or 
  /// (if xbase access) base_space() are not accessible for read and write
  /// or access control is disabled.
  ///
  bool state_is_not_read_write_accessible(bool xbase_access = false) const;

  ///
  /// The number of times access has been requested
  /// and granted without being released.
  ///
  int access_request_depth() const;

  ///
  /// Get read access to the state associated with this.
  ///
  virtual void get_read_access() const;

  ///
  /// Get read write access to the coordinates and property sections,
  /// which implies read access to the base space. If xbase_access,
  /// get read write access to the base space as well.
  /// If release_read_only_access is requested,
  /// read only access will be released then read_write_access will be requested,
  /// finally the same level of read_access as before will be requested.
  ///
  virtual void get_read_write_access(bool xbase_access,
                                     bool xrelease_read_only_access);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  virtual void release_access(bool xall = false) const;

  ///
  /// True if write access has been granted and released
  /// since the last call to clear_state_is_modified().
  ///
  bool state_is_modified() const;

  ///
  /// Sets the state_is_modified floag to false.
  ///
  void clear_state_is_modified();

  //@}

  //===========================================================================
  /// @name ANY FACET
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
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual field_vd* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual field_vd& operator=(const field_vd& xother);

  ///
  /// Assignment operator.
  ///
  field_vd& operator=(const sec_vd& xsection);

  ///
  /// Assignment operator.
  ///
  field_vd& operator=(const vd& xfiber);

  ///
  /// Assignment operator.
  ///
  field_vd& operator=(const vd_lite& xfiber);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

//=============================================================================
// NON-MEMBER FUNCTIONS
//=============================================================================

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
void push(const field_vd& xsrc, field_vd& xdst, bool xauto_access);

///
/// Pushes xsrc.property() to xdst.property().
///
SHEAF_DLL_SPEC
field_vd& operator>>(const field_vd& xsrc, field_vd& xdst);

///
/// Inserts field_vd xfield into ostream xos.
///
SHEAF_DLL_SPEC
std::ostream& operator<<(std::ostream& xos, const field_vd& xfield);

} // namespace fields


//==============================================================================

/// Include field_vd algebra function declarations.

#include "SheafSystem/field_vd_funcs.h"


#endif // ifndef FIELD_VD_H




