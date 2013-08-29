


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class fiber_bundles_namespace

#ifndef FIBER_BUNDLES_NAMESPACE_H
#define FIBER_BUNDLES_NAMESPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAVES_NAMESPACE_H
#include "sheaves_namespace.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

//#include "arg_list.h"

namespace fiber_bundle
{

using namespace sheaf;

class base_space_member;
class binary_section_space_schema_poset;
class sec_rep_descriptor_poset;
class sec_rep_space;
class section_space_schema_poset;
  

///
/// The standard fiber bundles name space;
/// extends the standard sheaves namespace by
/// defining base space, fiber space and section space schema.
///
class SHEAF_DLL_SPEC fiber_bundles_namespace : public sheaves_namespace
{

  // ===========================================================
  /// @name FIBER_BUNDLES_NAMESPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a fiber bundles namespace with name xname.
  ///
  fiber_bundles_namespace(const string& xname);

  ///
  /// Destructor
  ///
  virtual ~fiber_bundles_namespace();

//   ///
//   /// The name of the standard base space schema poset.
//   ///
//   static const string& standard_base_space_schema_poset_name();

//   ///
//   /// The name of the standard base space schema member.
//   ///
//   static const string& standard_base_space_schema_member_name();

  ///
  /// The path of the standard base space schema member.
  ///
  static const poset_path& standard_base_space_schema_path();

//   ///
//   /// The name of the standard base space member prototypes poset.
//   ///
//   static const string& standard_base_space_member_prototypes_poset_name();

  ///
  /// The name of the standard fiber space schema poset.
  ///
  static const string& standard_fiber_space_schema_poset_name();

//   ///
//   /// The name of the standard sec_rep_descriptor schema poset.
//   ///
//   static const string& standard_sec_rep_descriptor_schema_poset_name();

//   ///
//   /// The name of the standard sec_rep_descriptor schema poset.
//   ///
//   static const poset_path& standard_sec_rep_descriptor_schema_path();

//   ///
//   /// The name of the standard sec_rep_descriptor poset.
//   ///
//   static const string& standard_sec_rep_descriptor_poset_name();

//   ///
//   /// The path of the standard sec_rep_descriptor poset.
//   ///
//   static const poset_path& standard_sec_rep_descriptor_host_path();

  ///
  /// The name of the standard section space schema schema poset.
  ///
  static const string& standard_section_space_schema_schema_poset_name();

  ///
  /// Initialize all the prototypes needed by various factory methods,
  ///
  static void initialize_prototypes();

  ///
  /// Initialize the prototypes needed by poset factory method,
  ///
  static void initialize_poset_prototypes();

  ///
  /// Initialize the prototypes needed by crg interval factory method,
  ///
  static void initialize_crg_interval_prototypes();

  ///
  /// Initialize the prototypes needed by dof map factory method,
  ///
  static void initialize_dof_map_prototypes();

  ///
  /// Initialize the  prototypes needed by id space factory method,
  ///
  static void initialize_id_space_prototypes();

  ///
  /// The poset defining the schema for  base_space_poset, base_space_member and descendants.
  ///
  poset& base_space_schema_poset();

  ///
  /// The poset defining the schema for base_space_poset, base_space_member and descendants, const ver.
  ///
  const poset& base_space_schema_poset() const;

  ///
  /// The poset defining the prototype instances for base_space_member.
  ///
  base_space_poset& base_space_member_prototypes_poset();

  ///
  /// The poset defining the prototype instances for base_space_member, const ver.
  ///
  const base_space_poset& base_space_member_prototypes_poset() const;

protected:

  ///
  /// Initialize all the prototypes needed by various factory methods;
  /// virtual version.
  ///
  virtual void virtual_initialize_prototypes();

  ///
  /// Default constructor; creates an unattached handle.
  ///
  fiber_bundles_namespace();

  ///
  /// Covariant constructor.
  ///
  fiber_bundles_namespace(namespace_poset_member* xtop, namespace_poset_member* xbottom);

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  fiber_bundles_namespace(const fiber_bundles_namespace& xother);

private:

  ///
  /// The poset defining the schemas for base_space_member and descendaants.
  ///
  poset* _base_space_schema_poset;

  ///
  /// The poset defining the prototype instances for base_space_member.
  ///
  base_space_poset* _base_space_member_prototypes_poset;

  //@}

  /// @todo Remove.
 
//   // ===========================================================
//   /// @name BASE SPACE FACTORY METHODS FACET
//   // ===========================================================
//   //@{

// public:

//   ///
//   /// Find or create a new base space for meshes (blocks) of type B.
//   ///
//   template <typename B>
//   base_space_poset& new_base_space(const poset_path& xbase_space_path,
// 				   const arg_list& xargs = "",
// 				   const poset_path& xschema_path  = "",
// 				   int xmax_db = -1,
// 				   bool xauto_access = true);
  

// protected:

// private:

//   //@}


  //--------------------------------------------------------------------------
  // BEGIN NEW INTERFACE
 
  // ===========================================================
  /// @name STANDARD NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a standard path for fiber space of type F and
  /// suffix xfiber_suffix.
  ///
  template <typename F>
  poset_path
  standard_fiber_space_path(const string& xfiber_suffix) const;

  ///
  /// Create a standard schema path for fiber space of type F and
  /// suffix xfiber_suffix.
  ///
  template <typename F>
  poset_path
  standard_fiber_space_schema_path(const string& xfiber_suffix) const;

  ///
  /// Create a standard path for section space of type S, base space with
  /// path xbase_space_path, section representation with path xrep_path
  /// section suffix xsection_suffix and fiber suffix xfiber_suffix.
  ///
  template <typename S>
  poset_path
  standard_section_space_path(const poset_path& xbase_space_path,
			      const poset_path& xrep_path,
			      const string& xsection_suffix,
			      const string& xfiber_suffix) const;

  ///
  /// Create a standard schema poset path for section space of type S, base space
  /// with path xbase_space_path, section representation with path xrep_path
  /// and fiber suffix xfiber_suffix.
  ///
  template <typename S>
  poset_path
  standard_section_schema_space_path(const poset_path& xbase_space_path,
				     const poset_path& xrep_path,
				     const string& xfiber_suffix) const;

protected:

private:

  //@}
 

  // ===========================================================
  /// @name SHALLOW FIBER SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Find or create a fiber space with fibers of type F.
  /// at path xfiber_space_path. The arguments and schema
  /// specified by xfiber_space_args and xfiber_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename F>
  typename F::host_type&
  new_fiber_space_2(const poset_path& xfiber_space_path,
		  const arg_list& xfiber_space_args,
		  const poset_path& xfiber_space_schema_path,
		  bool xauto_access);

  ///
  /// Find or create a scalar fiber space with fibers of type F.
  /// at path xscalar_space_path. The arguments and schema
  /// specified by xscalar_space_args and xscalar_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename F>
  typename F::host_type&
  new_scalar_space_2(const poset_path& xscalar_space_path,
		   const arg_list& xscalar_space_args,
		   const poset_path& xscalar_space_schema_path,
		   bool xauto_access);

  ///
  /// Find or create a vector fiber space with fibers of type F.
  /// at path xvector_space_path. The arguments and schema
  /// specified by xvector_space_args and xvector_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename F>
  typename F::host_type&
  new_vector_space(const poset_path& xvector_space_path,
		   const arg_list& xvector_space_args,
		   const poset_path& xvector_space_schema_path,
		   bool xauto_access);

  ///
  /// Find or create a tensor fiber space with fibers of type F.
  /// at path xtensor_space_path. The arguments and schema
  /// specified by xtensor_space_args and xtensor_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename F>
  typename F::host_type&
  new_tensor_space(const poset_path& xtensor_space_path,
		   const arg_list& xtensor_space_args,
		   const poset_path& xtensor_space_schema_path,
		   bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name DEEP FIBER SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Find or create a fiber space with fibers of type F.
  /// at path, standard_fiber_space_path<F>(xfiber_suffix).
  ///
  template <typename F>
  typename F::host_type&
  new_fiber_space(const string& xfiber_suffix, bool xauto_access);

  ///
  /// Find or create a scalar fiber space with fibers of type F.
  /// at path, standard_fiber_space_path<F>(xfiber_suffix).
  ///
  template <typename F>
  typename F::host_type&
  new_scalar_space(const string& xfiber_suffix, bool xauto_access);

  ///
  /// Find or create a vector fiber space with fibers of type F.
  /// at path, standard_fiber_space_path<F>(xfiber_suffix).
  ///
  template <typename F>
  typename F::host_type&
  new_vector_space(const string& xfiber_suffix, bool xauto_access);

  ///
  /// Find or create a tensor fiber space with fibers of type F.
  /// at path, standard_fiber_space_path<F>(xfiber_suffix).
  ///
  template <typename F>
  typename F::host_type&
  new_tensor_space(const string& xfiber_suffix, bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name SHALLOW SECTION SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Find or create a section space with sections of type S.
  /// at path xsection_space_path.  The arguments and schema
  /// specified by xsection_space_args and xsection_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename S>
  typename S::host_type&
  new_section_space_2(const poset_path& xsection_space_path,
		    const arg_list& xsection_space_args,
		    const poset_path& xsection_space_schema_path,
		    bool xauto_access);

  ///
  /// Find or create a scalar section space with sections of type S.
  /// at path xscalar_space_path.  The arguments and schema
  /// specified by xscalar_space_args and xscalar_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename S>
  typename S::host_type&
  new_scalar_section_space_2(const poset_path& xscalar_space_path,
			   const arg_list& xscalar_space_args,
			   const poset_path& xscalar_space_schema_path,
			   bool xauto_access);

  ///
  /// Find or create a vector section space with sections of type S.
  /// at path xvector_space_path.  The arguments and schema
  /// specified by xvector_space_args and xvector_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename S>
  typename S::host_type&
  new_vector_section_space(const poset_path& xvector_space_path,
			   const arg_list& xvector_space_args,
			   const poset_path& xvector_space_schema_path,
			   bool xauto_access);

  ///
  /// Find or create a tensor section space with sections of type S.
  /// at path xtensor_space_path.  The arguments and schema
  /// specified by xtensor_space_args and xtensor_schema_path,
  /// respectively are used to create the fiber space.
  ///
  template <typename S>
  typename S::host_type&
  new_tensor_section_space(const poset_path& xtensor_space_path,
			   const arg_list& xtensor_space_args,
			   const poset_path& xtensor_space_schema_path,
			   bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name DEEP SECTION SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Find or create a section space with sections of type S.
  /// at path standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix).
  /// The fiber at path standard_fiber_space<S::fiber_type>(xfiber_suffix)
  /// is used to create the section space.
  ///
  template <typename S>
  typename S::host_type&
  new_section_space(const poset_path& xbase_space_path,
		    const poset_path& xrep_path,
		    const string& xsection_suffix,
		    const string& xfiber_suffix,
		    bool xauto_access);

  ///
  /// Find or create a scalar section space with sections of type S.
  /// at path standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix).
  /// The fiber at path standard_fiber_space<S::fiber_type>(xfiber_suffix)
  /// is used to create the section space.
  ///
  template <typename S>
  typename S::host_type&
  new_scalar_section_space(const poset_path& xbase_space_path,
			   const poset_path& xrep_path,
			   const string& xsection_suffix,
			   const string& xfiber_suffix,
			   bool xauto_access);

  ///
  /// Find or create a vector section space with sections of type S.
  /// at path standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix).
  /// The fiber at path standard_fiber_space<S::fiber_type>(xfiber_suffix)
  /// is used to create the section space.
  ///
  template <typename S>
  typename S::host_type&
  new_vector_section_space(const poset_path& xbase_space_path,
			   const poset_path& xrep_path,
			   const string& xsection_suffix,
			   const string& xfiber_suffix,
			   bool xauto_access);

  ///
  /// Find or create a tensor section space with sections of type S.
  /// at path standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix).
  /// The fiber at path standard_fiber_space<S::fiber_type>(xfiber_suffix)
  /// is used to create the section space.
  ///
  template <typename S>
  typename S::host_type&
  new_tensor_section_space(const poset_path& xbase_space_path,
			   const poset_path& xrep_path,
			   const string& xsection_suffix,
			   const string& xfiber_suffix,
			   bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name SHALLOW SECTION SPACE SCHEMA FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Find or create a section space schema poset for sections of type S
  /// at path xsection_schema_space_path.  The representation, base space
  /// and fiber space specified by xrep_path, xbase_space_path, and
  /// xfiber_space_path, respectively are used to create the section
  /// space schema.
  ///
  template <typename S>
  typename S::schema_host_type&
  new_section_schema_space(const poset_path& xsection_schema_space_path,
			   const poset_path& xbase_space_path,
			   const poset_path& xrep_path,
			   const poset_path& xfiber_space_path,
			   bool xauto_access);

  ///
  /// Find or create a scalar section space schema poset for sections of type S
  /// at path xsection_schema_space_path.  The representation, base space
  /// and fiber space specified by xrep_path, xbase_space_path, and
  /// xfiber_space_path, respectively are used to create the section
  /// space schema.
  ///
  template <typename S>
  typename S::schema_host_type&
  new_scalar_section_schema_space(const poset_path& xsection_schema_space_path,
				  const poset_path& xbase_space_path,
				  const poset_path& xrep_path,
				  const poset_path& xfiber_space_path,
				  bool xauto_access);

  ///
  /// Find or create a vector section space schema poset for sections of type S
  /// at path xsection_schema_space_path.  The representation, base space
  /// and fiber space specified by xrep_path, xbase_space_path, and
  /// xfiber_space_path, respectively are used to create the section
  /// space schema.
  ///
  template <typename S>
  typename S::schema_host_type&
  new_vector_section_schema_space(const poset_path& xsection_schema_space_path,
				  const poset_path& xbase_space_path,
				  const poset_path& xrep_path,
				  const poset_path& xfiber_space_path,
				  bool xauto_access);

  ///
  /// Find or create a tensor section space schema poset for sections of type S
  /// at path xsection_schema_space_path.  The representation, base space
  /// and fiber space specified by xrep_path, xbase_space_path, and
  /// xfiber_space_path, respectively are used to create the section
  /// space schema.
  ///
  template <typename S>
  typename S::schema_host_type&
  new_tensor_section_schema_space(const poset_path& xsection_schema_space_path,
				  const poset_path& xbase_space_path,
				  const poset_path& xrep_path,
				  const poset_path& xfiber_space_path,
				  bool xauto_access);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name DEEP SECTION SPACE SCHEMA FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Find or create a section space schema poset for sections of type S
  /// at path standard_section_schema_space_path(xbase_space_path, xrep_path, xfiber_suffix).
  ///
  template <typename S>
  typename S::schema_host_type&
  new_section_schema_space(const poset_path& xbase_space_path,
			   const poset_path& xrep_path,
			   const string& xfiber_suffix,
			   bool xauto_access);
  
  ///
  /// Find or create a scalar section space schema poset for sections of type S
  /// at path standard_section_schema_space_path(xbase_space_path, xrep_path, xfiber_suffix).
  ///
  template <typename S>
  typename S::schema_host_type&
  new_scalar_section_schema_space(const poset_path& xbase_space_path,
				  const poset_path& xrep_path,
				  const string& xfiber_suffix,
				  bool xauto_access);
  
  ///
  /// Find or create a vector section space schema poset for sections of type S
  /// at path standard_section_schema_space_path(xbase_space_path, xrep_path, xfiber_suffix).
  ///
  template <typename S>
  typename S::schema_host_type&
  new_vector_section_schema_space(const poset_path& xbase_space_path,
				  const poset_path& xrep_path,
				  const string& xfiber_suffix,
				  bool xauto_access);
  
  ///
  /// Find or create a tensor section space schema poset for sections of type S
  /// at path standard_section_schema_space_path(xbase_space_path, xrep_path, xfiber_suffix).
  ///
  template <typename S>
  typename S::schema_host_type&
  new_tensor_section_schema_space(const poset_path& xbase_space_path,
				  const poset_path& xrep_path,
				  const string& xfiber_suffix,
				  bool xauto_access);
  
protected:

private:

  //@}
 

  // END NEW INTERFACE
  //--------------------------------------------------------------------------
 

  // ===========================================================
  /// @name FIBER SPACE FACTORY METHODS FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Find or create a new fiber space for fibers of type F. 
  /// Simplified interface uses default values for prerequisite 
  /// vector and scalar spaces, if needed. To explictly specify 
  /// prerequisite spaces use the factory method for the category
  /// associated with F, i.e. new_vector_space, new_tensor_space, etc.
  ///
  template <typename F>
  typename F::host_type& new_fiber_space(const poset_path& xfiber_space_path = "",
					 const arg_list& xfiber_space_args = "",
					 const poset_path& xfiber_space_schema_path = "",
					 bool xauto_access = true);
 
  ///
  /// Create a new scalar fiber space.
  ///
  template <typename F>
  typename F::host_type& new_scalar_space(const poset_path& xscalar_space_path = "",
					  const arg_list& xscalar_space_args = "",
					  const poset_path& xscalar_space_schema_path = "",
					  bool xauto_access = true);

  ///
  /// Create a new vector fiber space.
  ///
  template <typename F>
  typename F::host_type& new_vector_space(const poset_path& xvector_space_path = "",
					  const arg_list& xvector_space_args = "",
					  const poset_path& xvector_space_schema_path = "",
					  const poset_path& xscalar_space_path = "",
					  const arg_list& xscalar_space_args = "",
					  const poset_path& xscalar_space_schema_path = "",
					  bool xauto_access = true);

  ///
  /// Create a new tensor fiber space.
  ///
  template <typename F>
  typename F::host_type& new_tensor_space(const poset_path& xfiber_space_path = "",
					  const arg_list& xfiber_space_args = "",
					  const poset_path& xfiber_space_schema_path = "",
					  const poset_path& xvector_space_path = "",
					  const arg_list& xvector_space_args = "",
					  const poset_path& xvector_space_schema_path = "",
					  const poset_path& xscalar_space_path = "",
					  const arg_list& xscalar_space_args = "",
					  const poset_path& xscalar_space_schema_path = "",
					  bool xauto_access = true);

  ///
  /// Create a new gln fiber space.
  ///
  template <typename F>
  typename F::host_type& new_group_space(const poset_path& xfiber_space_path = "",
					 const arg_list& xfiber_space_args = "",
					 const poset_path& xfiber_schema_path = "",
					 const poset_path& xvector_space_path = "",
					 const arg_list& xvector_space_args = "",
					 const poset_path& xvector_space_schema_path = "",
					 const poset_path& xscalar_space_path = "",
					 const arg_list& xscalar_space_args = "",
					 const poset_path& xscalar_space_schema_path = "",
					 bool xauto_access = true);

  ///
  /// Creates a new jacobian fiber space.
  ///
  template <typename F>
  typename F::host_type& new_jacobian_space(const poset_path& xfiber_space_path = "",
					    const arg_list& xfiber_space_args = "",
					    const poset_path& xfiber_schema_path = "",
					    const poset_path& xdomain_space_path = "",
					    const arg_list& xdomain_space_args = "",
					    const poset_path& xdomain_space_schema_path = "",
					    const poset_path& xrange_space_path = "",
					    const arg_list& xrange_space_args = "",
					    const poset_path& xrange_space_schema_path = "",
					    const poset_path& xscalar_space_path = "",
					    const arg_list& xscalar_space_args = "",
					    const poset_path& xscalar_space_schema_path = "",
					    bool xauto_access = true);

  ///
  /// Create a new tuple fiber space.
  ///
  template <typename F>
  typename F::host_type& new_tuple_space(const poset_path& xtuple_space_path = "",
					 const arg_list& xtuple_space_args = "",
					 const poset_path& xtuple_space_schema_path = "",
					 bool xauto_access = true);


  ///
  /// Implementation for new_fiber_space function template.
  /// 
  template <typename host_type> struct new_fiber_space_impl;

protected:
private:

  //@}


  // ===========================================================
  /// @name SECTION SPACE SCHEMA FACTORY METHODS FACET
  // ===========================================================
  //@{

public:


  ///
  /// Creates a new section space schema and member in
  /// namespace xns with path xsection_space_schema_path and representation, base space and
  /// fiber space specified by xrep_path, xbase_space_path, and xfiber_space_path,
  /// respectively. Note that the objects referred to by xrep_path,
  /// xbase_space_path, and xfiber_space_path must already exist and that
  /// xfiber_space_path specifies the fiber space, not the fiber schema.
  ///
  poset_path 
  new_section_space_schema(const poset_path& xsection_space_schema_path,
			   const poset_path& xrep_path,
			   const poset_path& xbase_space_path,
			   const poset_path& xfiber_space_path,
			   bool xauto_access);

  ///
  /// Finds or creates the section space schema specified 
  /// by the arguments for sections of type S.
  /// Simplified interface uses default values for prerequisite 
  /// vector and scalar spaces, if needed. To explictly specify 
  /// prerequisite spaces use the factory method for the category
  /// associated with S, i.e. new_vector_section_space_schema, etc.
  ///
  template <typename S>
  poset_path
  new_section_space_schema(const poset_path& xsection_space_schema_path = "",
			   const arg_list& xsection_space_schema_args = "",
			   const poset_path& xsection_space_schema_schema_path = "",
			   const poset_path& xrep_path = "",
			   const poset_path& xbase_space_path = "",
			   const poset_path& xfiber_space_path = "",
			   const arg_list& xfiber_space_args = "",
			   const poset_path& xfiber_space_schema_path = "",
			   bool xauto_access = true);

  ///
  /// Finds or creates the section space schema specified 
  /// by the arguments for sections of type S.
  ///
  template <typename S>
  poset_path
  new_scalar_section_space_schema(const poset_path& xsection_space_schema_path = "",
				  const arg_list& xsection_space_schema_args = "",
				  const poset_path& xsection_space_schema_schema_path = "",
				  const poset_path& xrep_path = "",
				  const poset_path& xbase_space_path = "",
				  const poset_path& xfiber_space_path = "",
				  const arg_list& xfiber_space_args = "",
				  const poset_path& xfiber_space_schema_path = "",
				  bool xauto_access = true);

  ///
  /// Finds or creates the section space schema specified 
  /// by the arguments for sections of type S.
  ///
  template <typename S>
  poset_path
  new_vector_section_space_schema(const poset_path& xsection_space_schema_path = "",
				  const arg_list& xsection_space_schema_args = "",
				  const poset_path& xsection_space_schema_schema_path = "",
				  const poset_path& xrep_path = "",
				  const poset_path& xbase_space_path = "",
				  const poset_path& xfiber_space_path = "",
				  const arg_list& xfiber_space_args = "",
				  const poset_path& xfiber_space_schema_path = "",
				  const poset_path& xscalar_space_path = "",
				  const arg_list& xscalar_space_args = "",
				  const poset_path& xscalar_space_schema_path = "",
				  bool xauto_access = true);

  ///
  /// Finds or creates the section space schema specified 
  /// by the arguments for sections of type S.
  ///
  template <typename S>
  poset_path
  new_tensor_section_space_schema(const poset_path& xsection_space_schema_path = "",
				  const arg_list& xsection_space_schema_args = "",
				  const poset_path& xsection_space_schema_schema_path = "",
				  const poset_path& xrep_path = "",
				  const poset_path& xbase_space_path = "",
				  const poset_path& xfiber_space_path = "",
				  const arg_list& xfiber_space_args = "",
				  const poset_path& xfiber_space_schema_path = "",
				  const poset_path& xvector_space_path = "",
				  const arg_list& xvector_space_args = "",
				  const poset_path& xvector_space_schema_path = "",
				  const poset_path& xscalar_space_path = "",
				  const arg_list& xscalar_space_args = "",
				  const poset_path& xscalar_space_schema_path = "",
				  bool xauto_access = true);

  ///
  /// Finds or creates the section space schema specified 
  /// by the arguments for sections of type S.
  ///
  template <typename S>
  poset_path
  new_tuple_section_space_schema(const poset_path& xsection_space_schema_path = "",
				  const arg_list& xsection_space_schema_args = "",
				  const poset_path& xsection_space_schema_schema_path = "",
				  const poset_path& xrep_path = "",
				  const poset_path& xbase_space_path = "",
				  const poset_path& xfiber_space_path = "",
				  const arg_list& xfiber_space_args = "",
				  const poset_path& xfiber_space_schema_path = "",
				  bool xauto_access = true);


  ///
  /// Implementation for new_section_space_schema function template.
  /// 
  template <typename host_type> struct new_section_space_schema_impl;

protected:
private:

  //@}


  // ===========================================================
  /// @name SECTION SPACE FACTORY METHODS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Clones the section space with path xsrc_space_path and
  /// initializes the new section space with path xsection_space_path,
  /// tables dofs initialized with xsection_space_args, if needed, and
  /// schema specified by xsection_space_schema_path.
  ///
  sec_rep_space&
  clone_section_space(const poset_path& xsrc_space_path,
		      const poset_path& xsection_space_path,
		      const arg_list& xsection_space_args = "",
		      const poset_path& xsection_space_schema_path = "",
		      bool xauto_access = true);

  ///
  /// Finds or creates the section space and section space_schema 
  /// specified by the arguments for sections of type S.
  /// Simplified interface uses default values for prerequisite 
  /// vector and scalar spaces, if needed. To explictly specify 
  /// prerequisite spaces use the factory method for the category
  /// associated with S, i.e. new_vector_section_space, etc.
  ///
  template <typename S>
  typename S::host_type&
  new_section_space(const poset_path& xsection_space_path,
		    const poset_path& xbase_space_path,
		    const poset_path& xrep_path = "",
		    bool xauto_access = true);

  ///
  /// Finds or creates the section space specified 
  /// by the arguments for sections of type S.
  /// Simplified interface uses default values for prerequisite 
  /// vector and scalar spaces, if needed. To explictly specify 
  /// prerequisite spaces use the factory method for the category
  /// associated with S, i.e. new_vector_section_space, etc.
  ///
  template <typename S>
  typename S::host_type&
  new_section_space(const poset_path& xsection_space_path = "",
		    const arg_list& xsection_space_args = "",
		    const poset_path& xsection_space_schema_path = "",
		    bool xauto_access = true);

  ///
  /// Create a new scalar section space.
  ///
  template <typename S>
  typename S::host_type&
  new_scalar_section_space(const poset_path& xscalar_space_path = "",
			   const arg_list& xscalar_space_args = "",
			   const poset_path& xscalar_space_schema_path = "",
			   bool xauto_access = true);

  ///
  /// Create a new vector section space.
  ///
  template <typename S>
  typename S::host_type&
  new_vector_section_space(const poset_path& xvector_space_path = "",
			   const arg_list& xvector_space_args = "",
			   const poset_path& xvector_space_schema_path = "",
			   const poset_path& xscalar_space_path = "",
			   const arg_list& xscalar_space_args = "",
			   const poset_path& xscalar_space_schema_path = "",
			   bool xauto_access = true);

  ///
  /// Create a new tensor section space.
  ///
  template <typename S>
  typename S::host_type&
  new_tensor_section_space(const poset_path& xtensor_space_path = "",
			   const arg_list& xtensor_space_args = "",
			   const poset_path& xtensor_space_schema_path = "",
			   const poset_path& xvector_space_path = "",
			   const arg_list& xvector_space_args = "",
			   const poset_path& xvector_space_schema_path = "",
			   const poset_path& xscalar_space_path = "",
			   const arg_list& xscalar_space_args = "",
			   const poset_path& xscalar_space_schema_path = "",
			   bool xauto_access = true);

  ///
  /// Create a new tuple section space.
  ///
  template <typename S>
  typename S::host_type&
  new_tuple_section_space(const poset_path& xtuple_space_path = "",
			  const arg_list& xtuple_space_args = "",
			  const poset_path& xtuple_space_schema_path = "",
			  bool xauto_access = true);

  ///
  /// Implementation for new_section_space function template.
  /// 
  template <typename host_type> struct new_section_space_impl;

protected:
private:

  //@}


  // ===========================================================
  /// @name PATH COMPLETION FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// The path created by copying xprimary_path, if it is not empty, 
  /// or by copying xsecondary_path, if it is not empty or by copying
  /// xdefault_path.
  ///
  poset_path completed_path(const poset_path& xpath, 
			    const poset_path& xsecondary_path, 
			    const poset_path& xdefault_path) const;
  
  ///
  /// The full path created by copying xprimary_path, if it is full, 
  /// or by copying xsecondary_path, if it is full or by copying
  /// xdefault_path.
  ///
  poset_path completed_full_path(const poset_path& xpath, 
				 const poset_path& xsecondary_path, 
				 const poset_path& xdefault_path) const;
  
  ///
  /// The schema path created by coping xschema_path, if it is full, or
  /// by copying the standard schema path for spaces of type S.
  ///
  template <typename S>
  poset_path
  completed_schema_path(const poset_path& xpath) const;  

protected:

  ///
  /// The path of the underlying vector space 
  /// of the fiber space with path xfiber_space_path.
  ///
  poset_path vector_space_path(const poset_path& xfiber_space_path, bool xauto_access) const;

  ///
  /// The path of the underlying space of scalars 
  /// of the vector space with path xvector_space_path.
  ///
  poset_path scalar_space_path(const poset_path& xvector_space_path, bool xauto_access) const;

private:

  //@}


  // ===========================================================
  /// @name FIBER/SECTION FACTORY METHOD PATH COMPLETION FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Completed space path for fiber or section spaces of type S.
  /// The space path created by copying xpath, if it is not empty, 
  /// or using the default value for spaces of type S.
  ///
  template <typename S>
  poset_path 
  completed_space_path(const poset_path& xpath) const;
  
  ///
  /// Completed tensor index for tensor fiber or section spaces of type S.
  /// The tensor degree p associated with completed_space_path, if it exists, 
  /// or with xspace_args, if it contains arg "p", or the default for S.
  ///
  template <typename S>
  int completed_p(const poset_path& xspace_path, 
		  const arg_list& xspace_args,
		  bool xauto_access) const;

  ///
  /// Completed vector space path for tensor fiber or section spaces of type S.
  /// The vector_space path created by copying the actual vector_space_path associated
  /// with completed_space_path, if it exists, or by copying xvector_space_path, 
  /// if it is not empty, or by copying the value in xspace_args, if it is not empty,
  /// or by copying the standard value for vector spaces of type S::vector_space_type.
  ///
  template <typename S>
  poset_path 
  completed_vector_space_path(const poset_path& xspace_path, 
			      const poset_path& xvector_space_path, 
			      const arg_list& xspace_args,
			      bool xauto_access) const;
  
  ///
  /// Completed scalar space path for vector fiber or section spaces of type S.
  /// The scalar_space path created by copying the actual scalar_space_path associated
  /// with completed_space_path, if it exists, or by copying xscalar_space_path, 
  /// if it is not empty, or by copying the value in xspace_args or 
  /// by copying the standard value for scalar spaces of type S::scalar_type. 
  ///
  template <typename S>
  poset_path 
  completed_scalar_space_path(const poset_path& xspace_path, 
			      const poset_path& xscalar_space_path, 
			      const arg_list& xspace_args,
			      bool xauto_access) const;
  
  ///
  /// Completed scalar space path for tensor fiber or section spaces of type S.
  /// The scalar_space path created by copying the actual scalar_space_path associated
  /// with completed_vector_space_path, if it exists, or by copying xscalar_space_path, 
  /// if it is not empty, or by copying the value in xvector_space_args or 
  /// by copying the standard value for scalar spaces of type S::scalar_type. 
  ///
  template <typename S>
  poset_path 
  completed_tensor_scalar_space_path(const poset_path& xspace_path, 
				     const poset_path& xvector_space_path, 
				     const arg_list& xspace_args,
				     const poset_path& xscalar_space_path, 
				     const arg_list& xvector_space_args,
				     bool xauto_access) const;
  
  ///
  /// Completed scalar space path for Jacobian fiber or section spaces of type J.
  /// The scalar_space path created by copying the actual scalar_space_path associated
  /// with completed_domain_space_path, if it exists, or by copying xscalar_space_path, 
  /// if it is not empty, or by copying the value in xdomain_space_args or 
  /// by copying the standard value for scalar spaces of type J::scalar_type. 
  ///
  template <typename J>
  poset_path 
  completed_jacobian_scalar_space_path(const poset_path& xspace_path, 
				       const poset_path& xdomain_space_path, 
				       const arg_list& xspace_args,
				       const poset_path& xscalar_space_path, 
				       const arg_list& xdomain_space_args,
				       bool xauto_access) const;

  ///
  /// Completed domain space path for jacobian fiber or section spaces of type J.
  /// The domain_space path created by copying the actual domain_space_path associated
  /// with completed_space_path, if it exists, or by copying xdomain_space_path, 
  /// if it is not empty, or by copying the value in xspace_args, if it is not empty,
  /// or by copying the standard value for domain spaces of type J::domain_type.
  ///
  template <typename J>
  poset_path 
  completed_domain_space_path(const poset_path& xspace_path, 
			      const poset_path& xdomain_space_path, 
			      const arg_list& xspace_args,
			      bool xauto_access) const;
  
  ///
  /// Completed range space path for jacobian fiber or section spaces of type J.
  /// The range_space path created by copying the actual range_space_path associated
  /// with completed_space_path, if it exists, or by copying xrange_space_path, 
  /// if it is not empty, or by copying the value in xspace_args, if it is not empty,
  /// or by copying the standard value for range spaces of type J::range_type.
  ///
  template <typename J>
  poset_path 
  completed_range_space_path(const poset_path& xspace_path, 
			      const poset_path& xrange_space_path, 
			      const arg_list& xspace_args,
			      bool xauto_access) const;  

protected:

private:

  //@}


  // ===========================================================
  /// @name SECTION SCHEMA FACTORY METHOD PATH COMPLETION FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// The section space schema path created by copying xpath, if it is full,
  /// or using the xrep_path, xbase_space_path, and xfiber_space_path as completed
  /// for sections of type S.
  ///
  template <typename S>
  poset_path
  completed_section_space_schema_path(const poset_path& xpath,
				      const poset_path& xrep_path,
				      const poset_path& xbase_space_path,
				      const poset_path& xfiber_space_path,
				      const arg_list& xargs,
				      bool xauto_access) const;
  
  ///
  /// The rep path created by copying the actual rep_path associated with 
  /// xsection_space_schema_path, if it exists, or by copying xrep_path, 
  /// if it is full, or copying the value in xargs, if it is full, or 
  /// copying the standard value for section spaces of type S.
  ///
  template <typename S>
  poset_path 
  completed_rep_path(const poset_path& xsection_space_schema_path, 
		     const poset_path& xrep_path, 
		     const arg_list& xargs,
		     bool xauto_access) const;

  ///
  /// Completed fiber space path for section spaces of type S.
  /// The fiber_space path created by copying the actual fiber_space_path associated with 
  /// xsection_space_schema_path, if it exists, or by copying xfiber_space_path, 
  /// if it is full, or copying the value in xsection_space_schema_args, if it is full, or 
  /// copying the standard value for section spaces of type S.
  ///
  template <typename S>
  poset_path 
  completed_fiber_space_path(const poset_path& xsection_space_schema_path, 
			     const poset_path& xfiber_space_path, 
			     const arg_list& xsection_space_schema_args,
			     bool xauto_access) const;

  ///
  /// Completed tensor index for tensor section spaces of type S.
  /// The tensor degree p associated with completed_fiber_space_path, if it exists, 
  /// or with xfiber_space_args, if it contains arg "p", or the default for S::fiber_type.
  ///
  template <typename S>
  int
  completed_p(const poset_path& xsection_space_schema_path, 
	      const poset_path& xfiber_space_path, 
	      const arg_list& xsection_space_schema_args,
	      const arg_list& xfiber_space_args,
	      bool xauto_access) const;
  
  ///
  /// The base space path created by copying the actual base space path associated with 
  /// xsection_space_schema_path, if it exists, or by copying xbase_space_path, 
  /// if it is full, or copying the value in xsection_space_schema_args, if it is full.
  ///
  poset_path completed_base_space_path(const poset_path& xsection_space_schema_path, 
				       const poset_path& xbase_space_path, 
				       const arg_list& xsection_space_schema_args,
				       bool xauto_access) const;
  
  ///
  /// Completed vector space path for tensor section spaces of type S
  /// The vector_space path created by copying the actual vector_space_path associated
  /// with completed_fiber_space_path, if it exists, or by copying xvector_space_path, 
  /// if it is not empty, or by copying the value in xfiber_space_args, if it is not empty,
  /// or by copying the standard value for vector spaces for section spaces of type S.
  ///
  template <typename S>
  poset_path 
  completed_vector_space_path(const poset_path& xsection_space_schema_path, 
			      const poset_path& xfiber_space_path, 
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xvector_space_path, 
			      const arg_list& xfiber_space_args,
			      bool xauto_access) const;
  
  ///
  /// Completed scalar space path for vector section spaces of type S.
  /// The scalar_space path created by copying the actual scalar_space_path associated
  /// with completed_fiber_space_path, if it exists, or by copying xscalar_space_path, 
  /// if it is full, or by copying the standard value for scalar spaces of 
  /// type S::fiber_type::scalar_type.
  ///
  template <typename S>
  poset_path 
  completed_section_scalar_space_path(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const poset_path& xscalar_space_path, 
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;
  
  ///
  /// Completed scalar space path for tensor section spaces of type S.
  /// The scalar_space path created by copying the actual scalar_space_path associated
  /// with completed_fiber_space_path, if it exists, or by copying xscalar_space_path, 
  /// if it is full, or by copying the standard value for scalar spaces of 
  /// type S::fiber_type::scalar_type.
  ///
  template <typename S>
  poset_path 
  completed_scalar_space_path(const poset_path& xsection_space_schema_path, 
			      const poset_path& xfiber_space_path, 
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xvector_space_path, 
			      const arg_list& xfiber_space_args,
			      const poset_path& xscalar_space_path, 
			      const arg_list& xvector_space_args,
			      bool xauto_access) const;
  
protected:

private:

  //@}


  // ===========================================================
  /// @name FIBER/SECTION FACTORY METHOD PATH AVAILABILITY QUERY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Space availability query for fiber or section spaces of type S.
  /// True if the space referred to by completed_space_path 
  /// path_is_auto_read_available<F>.
  ///
  template <typename S>
  bool 
  completed_space_path_is_available(const poset_path& xspace_path, 
				    bool xauto_access) const;
  
  ///
  /// Vector space availability query for tensor fiber or section spaces of type S.
  /// True if the space referred to by completed_space_path 
  /// already exists or if completed_vector_space_path is auto_read_available and 
  /// can conform to S::vector_space_type::host_type, for spaces of type S.
  ///
  template <typename S>
  bool 
  completed_vector_space_path_is_available(const poset_path& xspace_path, 
					   const poset_path& xvector_space_path, 
					   const arg_list& xspace_args,
					   bool xauto_access) const;
  
  ///
  /// Scalar space availability query for vector fiber or section spaces of type S.
  /// True if completed_scalar_space_path is_auto_read_available<S::scalar_type::host_type>
  ///
  template <typename S>
  bool 
  completed_scalar_space_path_is_available(const poset_path& xspace_path, 
					   const poset_path& xscalar_space_path, 
					   const arg_list& xspace_args,
					   bool xauto_access) const;
  
  ///
  /// Scalar space availability query for tensor fiber or section spaces of type S.
  /// True if completed_tensor_scalar_space_path is_auto_read_available<S::scalar_type::host_type>
  ///
  template <typename S>
  bool 
  completed_tensor_scalar_space_path_is_available(const poset_path& xspace_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xspace_args,
						  const poset_path& xscalar_space_path, 
						  const arg_list& xvector_space_args,
						  bool xauto_access) const;
  
  ///
  /// Scalar space availability query for Jacobian fiber or section spaces of type S.
  /// True if completed_jacobian_scalar_space_path is_auto_read_available<S::scalar_type::host_type>
  ///
  template <typename S>
  bool 
  completed_jacobian_scalar_space_path_is_available(const poset_path& xspace_path, 
						    const poset_path& xdomain_space_path, 
						    const arg_list& xspace_args,
						    const poset_path& xscalar_space_path, 
						    const arg_list& xdomain_space_args,
						    bool xauto_access) const;
  
  ///
  /// Domain space availability query for jacobian fiber or section spaces of type J.
  /// True if the space referred to by completed_space_path 
  /// already exists or if completed_domain_space_path is auto_read_available and 
  /// can conform to J::domain_type::host_type, for spaces of type J.
  ///
  template <typename J>
  bool 
  completed_domain_space_path_is_available(const poset_path& xspace_path, 
					   const poset_path& xdomain_space_path, 
					   const arg_list& xspace_args,
					   bool xauto_access) const;
  
  ///
  /// Range space availability query for jacobian fiber or section spaces of type J.
  /// True if the space referred to by completed_space_path 
  /// already exists or if completed_range_space_path is auto_read_available and 
  /// can conform to J::range_type::host_type, for spaces of type J.
  ///
  template <typename J>
  bool 
  completed_range_space_path_is_available(const poset_path& xspace_path, 
					   const poset_path& xrange_space_path, 
					   const arg_list& xspace_args,
					   bool xauto_access) const;
  

protected:

private:

  //@}


  // ===========================================================
  /// @name SECTION SCHEMA FACTORY METHOD PATH AVAILABILITY QUERY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if completed_section_space_schema_path<S>(same args)
  /// either exists, is auto_read_accessible and conforms to section_space_schema_poset
  /// does not exist and hence can be created to conform.
  ///
  template <typename S>
  bool 
  completed_section_space_schema_path_is_available(const poset_path& xpath,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xargs,
						   bool xauto_access) const;
  
  ///
  /// True if the space referred to by completed_section_space_schema_path already exists
  /// or if completed_rep_path is auto_read_accessible.
  ///
  template <typename S>
  bool 
  completed_rep_path_is_accessible(const poset_path& xsection_space_schema_path, 
				   const poset_path& xrep_path, 
				   const poset_path& xbase_space_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xargs,
				   bool xauto_access) const;
  
  ///
  /// True if the space referred to by completed_section_space_schema_path already exists
  /// or if completed_base_space_path is auto_read_accessible.
  ///
  template <typename S>
  bool 
  completed_base_space_path_is_accessible(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const poset_path& xbase_space_path, 
					  const poset_path& xfiber_space_path, 
					  const arg_list& xsection_space_schema_args,
					  bool xauto_access) const;
  
  ///
  /// Fiber space availability query for section spaces of type S.
  /// True if the section space referred to by completed_section_space_schema_path 
  /// already exists or if completed_fiber_space_path is auto_read_available and 
  /// can conform to S::fiber_type::host_type for sections of type S.
  ///
  template <typename S>
  bool 
  completed_fiber_space_path_is_available(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const poset_path& xbase_space_path, 
					  const poset_path& xfiber_space_path, 
					  const arg_list& xsection_space_schema_args,
					  bool xauto_access) const;
  
  ///
  /// Vector space availability query for tensor section spaces of type S.
  /// True if the section space referred to by completed_section_space_schema_path 
  /// already exists or if completed_vector_space_path is auto_read_available and 
  /// can conform to S::fiber_type::vector_space_type::host_type.
  ///
  template <typename S>
  bool 
  completed_vector_space_path_is_available(const poset_path& xsection_space_schema_path, 
					   const poset_path& xrep_path, 
					   const poset_path& xbase_space_path, 
					   const poset_path& xfiber_space_path, 
					   const arg_list& xsection_space_schema_args,
					   const poset_path& xvector_space_path, 
					   const arg_list& xfiber_space_args,
					   bool xauto_access) const;  
  
  ///
  /// Scalar space availability query for vector section spaces of type S.
  /// True if the section space referred to by completed_section_space_schema_path 
  /// already exists or if completed_scalar_space_path is auto_read_available and 
  /// can conform to S::fiber_type::scalar_type::host_type.
  ///
  template <typename S>
  bool 
  completed_scalar_space_path_is_available(const poset_path& xsection_space_schema_path, 
					   const poset_path& xrep_path, 
					   const poset_path& xbase_space_path, 
					   const poset_path& xfiber_space_path, 
					   const arg_list& xsection_space_schema_args,
					   const poset_path& xscalar_space_path, 
					   const arg_list& xfiber_space_args,
					   bool xauto_access) const;
  
  ///
  /// Scalar space availability query for tensor section spaces of type S.
  /// True if the section space referred to by completed_section_space_schema_path 
  /// already exists or if completed_scalar_space_path is auto_read_available and 
  /// can conform to S::fiber_type::scalar_type::host_type. Tensor section space version.
  ///
  template <typename S>
  bool 
  completed_scalar_space_path_is_available(const poset_path& xsection_space_schema_path, 
					   const poset_path& xrep_path, 
					   const poset_path& xbase_space_path, 
					   const poset_path& xfiber_space_path, 
					   const arg_list& xsection_space_schema_args,
					   const poset_path& xvector_space_path, 
					   const arg_list& xfiber_space_args,
					   const poset_path& xscalar_space_path, 
					   const arg_list& xvector_space_args,
					   bool xauto_access) const;
  
protected:

private:

  //@}


  // ===========================================================
  /// @name MISCELLANEOUS FACTORY METHOD QUERY FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// True if and only if completed_schema_path(xpath) is auto read accessible
  /// and conforms to the standard schema for spaces of type S.
  ///
  template <typename S>
  bool completed_schema_path_conforms_to(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if xargs are empty or if xargs conforms to
  /// completed_schema_path<S>(xpath).
  ///
  template <typename S>
  bool args_conform_to_completed_schema_path(const arg_list& xargs, 
					     const poset_path& xpath, 
					     bool xauto_access) const;
   
  ///
  /// True if and only if the poset specified by xpath 
  /// exists and conforms to at0_space.
  ///
  bool is_scalar_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath
  /// exists and conforms to at1_space.
  ///
  bool is_vector_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath 
  /// exists and conforms to tp_space.
  ///
  bool is_tensor_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath 
  /// is_tensor_space but !is_vector_space and !is_scalar_space.
  ///
  bool is_strict_tensor_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath 
  /// exists and conforms to jcb_space.
  ///
  bool is_jcb_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath 
  /// exists and conforms to vd_space.
  ///
  bool is_abstract_vector_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath 
  /// is_abstract_vecto_space but !is_tensor_space and !is_jcb_space.
  ///
  bool is_strict_abstract_vector_space(const poset_path& xpath, bool xauto_access) const;
  
  ///
  /// True if and only if the poset specified by xpath 
  /// exists and conforms to gln_space.
  ///
  bool is_gln_space(const poset_path& xpath, bool xauto_access) const;

protected:

private:

  //@}
 

  // ===========================================================
  /// @name BASE SPACE DEFINITIONS FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Create schema and prototypes for standard base space member types.
  ///
  void make_base_space_definitions();

  ///
  /// Create schema poset for standard base space member types.
  ///
  void make_base_space_schema_poset();

  ///
  /// Create schema members for standard base space member types.
  ///
  virtual void make_base_space_schema_members();

  ///
  /// Create standard base space member prototypes poset.
  ///
  void make_base_space_member_prototypes_poset();

  ///
  /// Create standard base space member prototypes.
  ///
  virtual void make_base_space_member_prototypes(base_space_poset* xspace);

  ///
  /// Create prototype for a single point (i.e. a vertex) in poset xspace.
  ///
  void make_point_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a line segement (i.e. an edge) in poset xspace.
  ///
  void make_segment_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a line segement complex,
  /// i.e. an edge and the veritices it contains, in poset xspace.
  ///
  void make_segment_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a triangle in poset xspace.
  ///
  void make_triangle_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a triangle with nodes in poset xspace.
  ///
  void make_triangle_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a triangle with edges and nodes in poset xspace.
  ///
  void make_triangle_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a quad in poset xspace.
  ///
  void make_quad_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a quad with nodes in poset xspace.
  ///
  void make_quad_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a quad with edges and nodes in poset xspace.
  ///
  void make_quad_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a general polygon in poset xspace.
  ///
  void make_general_polygon_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a tetrahedron in poset xspace.
  ///
  void make_tetra_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a tetrahedron with nodes in poset xspace.
  ///
  void make_tetra_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a tetrahedron with faces, edges, and nodes in poset xspace.
  ///
  void make_tetra_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex in poset xspace.
  ///
  void make_hex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex with nodes in poset xspace.
  ///
  void make_hex_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex with faces and nodes in poset xspace.
  ///
  void make_hex_faces_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex with faces, edges, and nodes in poset xspace.
  ///
  void make_hex_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a general polyhedron in poset xspace.
  ///
  void make_general_polyhedron_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for an unstructured block in poset xspace.
  ///
  void make_unstructured_block_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 1D structured block in poset xspace.
  ///
  void make_structured_block_1d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 2D structured block in poset xspace.
  ///
  void make_structured_block_2d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 3D structured block in poset xspace.
  ///
  void make_structured_block_3d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 1D point block in poset xspace.
  ///
  void make_point_block_1d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 2D point block in poset xspace.
  ///
  void make_point_block_2d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 3D point block in poset xspace.
  ///
  void make_point_block_3d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a part in poset xspace.
  ///
  void make_part_prototype(base_space_poset* xspace);

  ///
  /// Initializes the dofs in  base space member prototype
  /// dof map xmap to default values.
  ///
  void init_prototype_dof_map(base_space_member& xproto, int xdb);

private:

  //@}


  // ===========================================================
  /// @name FIBER SPACE DEFINITIONS FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Create standard fiber schema and fiber spaces.
  ///
  void make_fiber_space_definitions();

  ///
  /// Create schema poset for standard fiber space types.
  ///
  void make_fiber_space_schema_poset();

  ///
  /// Create schema members for standard fiber space types.
  ///
  virtual void make_fiber_space_schema_members();

  ///
  /// Create standard fiber spaces.
  ///
  virtual void make_fiber_spaces();

private:

  //@}


  // ===========================================================
  /// @name SECTION SPACE DEFINITIONS FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Create standard section representations and section schema.
  ///
  void make_section_space_definitions();

  ///
  /// Create schema poset for standard sec_rep_descritpors.
  ///
  void make_sec_rep_descriptor_schema_poset();

  ///
  /// Create schema members for standard sec_rep_descriptors.
  ///
  virtual void make_sec_rep_descriptor_schema_members();

  ///
  /// Create the standard sec_rep_descriptor poset.
  ///
  void make_sec_rep_descriptor_poset();

  ///
  /// Create standard section representation descriptors in poset xhost.
  ///
  virtual void make_sec_rep_descriptors(sec_rep_descriptor_poset* xhost);

  ///
  /// Create schema poset for standard section space schema.
  ///
  void make_section_space_schema_schema_poset();

  ///
  /// Create schema members for standard section space schema.
  ///
  virtual void make_section_space_schema_schema_members();

private:

  //@}


  // ===========================================================
  /// @name NAMESPACE_POSET FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Creates additional  members for this namespace.
  ///
  virtual void initialize_additional_members();

  ///
  /// Links xmbr into the appropriate group.
  ///
  virtual void link_poset(const namespace_poset_member& xmbr);

private:

  //@}
 

  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

protected:

  ///
  /// Attaches the handle data members when this handle
  /// is attached to a state. Intended to be redefined in
  /// descendants to handle additional data members defined there.
  ///
  virtual void attach_handle_data_members();

private:

  //@}

};

// Declarations of specializations needed by fiber space factory method facet. 

class at0_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<at0_space>;

class at1_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<at1_space>;

class atp_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<atp_space>;

class stp_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<stp_space>;

class tp_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<tp_space>;

class vd_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<vd_space>;

class gln_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<gln_space>;

class jcb_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<jcb_space>;

class tuple_space;  
template<> struct fiber_bundles_namespace::new_fiber_space_impl<tuple_space>;

// Declarations of specializations needed by section space schema factory method facet. 

class sec_at0_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_at0_space>;

class sec_at1_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_at1_space>;

class sec_atp_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_atp_space>;

class sec_stp_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_stp_space>;

class sec_tp_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_tp_space>;

class sec_vd_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_vd_space>;

class sec_tuple_space;  
template<> struct fiber_bundles_namespace::new_section_space_schema_impl<sec_tuple_space>;


// Declarations of specializations needed by section space factory method facet. 

template<> struct fiber_bundles_namespace::new_section_space_impl<sec_at0_space>;
template<> struct fiber_bundles_namespace::new_section_space_impl<sec_at1_space>;
template<> struct fiber_bundles_namespace::new_section_space_impl<sec_atp_space>;
template<> struct fiber_bundles_namespace::new_section_space_impl<sec_stp_space>;
template<> struct fiber_bundles_namespace::new_section_space_impl<sec_tp_space>;
template<> struct fiber_bundles_namespace::new_section_space_impl<sec_vd_space>;
template<> struct fiber_bundles_namespace::new_section_space_impl<sec_tuple_space>;
 
} // namespace fiber_bundle

#endif // ifndef FIBER_BUNDLES_NAMESPACE_H
