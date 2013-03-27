
// $RCSfile: vd_field.h,v $ $Revision: 1.21 $ $Date: 2013/03/21 16:28:33 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class vd_field

#ifndef VD_FIELD_H
#define VD_FIELD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace sheaf
{
template <class T> class name_map;
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
}

namespace fields
{

class discretization_push_action;
class property_disc_iterator;
class put_property_dofs_action;
class sec_ed_invertible;

///
/// A vd-valued property as a function of global coordinates.
///
class SHEAF_DLL_SPEC vd_field : public any
{
  //===========================================================================
  /// @name VD_FIELD FACET
  //===========================================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  ///
  vd_field();

  ///
  /// Copy constructor
  ///
  ///
  vd_field(const vd_field& xother, bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property xproperty.
  ///
  vd_field(const sec_ed& xcoordinates, const sec_vd& xproperty,
           bool xauto_access);

  ///
  /// Create an instance with coordinates specified by xcoordinates_path
  /// and property specified by xproperty_path in name space xns.
  ///
  vd_field(namespace_poset& xns,
           const poset_path& xcoordinates_path,
           const poset_path& xproperty_path,
           bool xauto_access);

  ///
  /// Create an instance with coordinates xcoordinates and property defined
  /// by pushing the property of xother to the base space of xcoordinates.
  ///
  vd_field(const sec_ed& xcoordinates, const vd_field& xother,
           bool xauto_access);

  ///
  /// Destructor
  ///
  virtual ~vd_field();

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
  namespace_poset* name_space() const;

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
  static
  void
  property_dof_function_example(block<sec_vd_value_type>& xglobal_coords,
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
  void print_property_dofs(ostream& xos,
                           property_dof_function_type xproperty_dofs_fcn,
                           const string& xtitle_text,
                           bool xzero_specified,
                           bool xauto_access) const;

  ///
  /// True if this has the same property fiber as xother.
  ///
  bool same_property_fiber_schema(const vd_field& xother,
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
  void property_at_coordinates(const block<sec_vd_value_type>& xcoord,
                               block<sec_vd_value_type>& xprop) const;

  ///
  /// The value of the property at the given global coordinates.
  ///
  void property_at_coordinates(sec_vd_value_type xcoord_base[],
                               int xcoord_ct,
                               sec_vd_value_type xprop_base[],
                               int xprop_ub) const;

  ///@todo Specialize name_map for scoped_index.

  ///
  /// Creates a decomposition of the base space such that the value
  /// of property() is constant on each member.
  //// @hack this function belongs in sec_at0, but is put here
  //// temporarily to avoid problems merging with branch refactor-8.
  ////
  subposet* embed_property(const string& xresult_name,
                           //name_map<client_index>& xresult_member_names,
                           name_map<int>& xresult_member_names,
                           bool xauto_access);


  ///
  /// Deletes field xfield and all associated section spaces, section schema spaces,
  /// and base space, if they are no longer being used. If xdelete_coord_fiber
  /// delete the coordinate fiber space, if it is no longer beinbg used, and
  /// similarly for xdelete_prop_fiber.
  ///
  static void delete_field_spaces(vd_field* xfield,
                                  bool xdelete_coord_fiber,
                                  bool xdelete_prop_fiber);

private:

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
  /// True if this handle has a state associated with it.
  ///
  virtual bool is_attached() const;

  ///
  /// True if the state is accessible for read access but not for write.
  ///
  bool state_is_read_only_accessible() const;

  ///
  /// True if the state is accessible for read.
  ///
  bool state_is_read_accessible() const;

  ///
  /// True if coordinates(), property() and (if xbase access) base_space()
  /// are accessible for write. Implies state is accessible for read.
  ///
  bool state_is_read_write_accessible(bool xbase_access = false) const;

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
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual vd_field* clone() const;

  ///
  /// Assignment operator
  ///
  ///
  vd_field& operator=(const vd_field& xother);

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
void SHEAF_DLL_SPEC push_to(const vd_field& xsrc, vd_field& xdst, bool xauto_access);

///
/// Pushes xsrc.property() to xdst.property().
///
vd_field& SHEAF_DLL_SPEC operator>>(const vd_field& xsrc, vd_field& xdst);

///
/// Inserts vd_field xfield into ostream xos.
///
ostream& SHEAF_DLL_SPEC operator<<(ostream& xos, const vd_field& xfield);

//=============================================================================
// NON-MEMBER FUNCTIONS (ALGEBRA)
//=============================================================================

///
/// x0 add x1 (pre-allocated version).
///
void SHEAF_DLL_SPEC add(const vd_field& x0, const vd_field& x1, vd_field& xresult,
         bool xauto_access);

///
/// x0 add_equal x1 (self-allocated version);
/// synonym for add(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC add_equal(vd_field& xresult, const vd_field& xother, bool xauto_access);

///
/// x0 subtract x1 (pre-allocated version).
///
void SHEAF_DLL_SPEC subtract(const vd_field& x0, const vd_field& x1, vd_field& xresult,
              bool xauto_access);

///
/// x0 subtract_equal x1 (self-allocated version);
/// synonym for subtract(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC subtract_equal(vd_field& xresult, const vd_field& xother,
                    bool xauto_access);

///
/// x0 multiplied by x1 (pre-allocated version).
///
void SHEAF_DLL_SPEC multiply(const vd_field& x0, const sec_at0& x1, vd_field& xresult,
              bool xauto_access);

///
/// xresult multiply_equal xresult (pre-allocated version);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC multiply_equal(vd_field& xresult, const sec_at0& xother,
                    bool xauto_access);

///
/// x0 multiplied by x1 (a constant) (pre-allocated version).
///
void SHEAF_DLL_SPEC multiply(const vd_field& x0, const vd_value_type& x1, vd_field& xresult,
              bool xauto_access);

///
/// xresult multiply_equal xother (pre-allocated version);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC multiply_equal(vd_field& xresult, const vd_value_type& xother,
                    bool xauto_access);

///
/// x0 divided by x1 (pre-allocated version).
///
void SHEAF_DLL_SPEC divide(const vd_field& x0, const sec_at0& x1, vd_field& xresult,
            bool xauto_access);

///
/// xresult divide_equal xother (pre-allocated version);
/// synonym for divide(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC divide_equal(vd_field& xresult, const sec_at0& xother,
                  bool xauto_access);

///
/// x0 divided by x1 (a constant) (pre-allocated version).
///
void SHEAF_DLL_SPEC divide(const vd_field& x0, const vd_value_type& x1, vd_field& xresult,
            bool xauto_access);

///
/// xresult divide_equal xother (pre-allocated version);
/// synonym for divide(xresult, xother, xresult, xauto_access).
///
void SHEAF_DLL_SPEC divide_equal(vd_field& xresult, const vd_value_type& xother,
                  bool xauto_access);

///
/// Contraction of vector xvector on covector xcovector
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC contract(const vd_field& xvector, const vd_field& xcovector,
              sec_at0& xresult, bool xauto_access);



} // namespace fields

#endif // ifndef VD_FIELD_H
