
//
// $RCSfile$ $Revision$ $Date$
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Contains all the template directives for the sheaves component.
//

//=============================================================================
// namespace_poset template directives:
//=============================================================================

//
// Define namespace poset directives.
//

%define %poset_factory_templates(P)

%template(new_member_poset_ ## P) sheaf::namespace_poset::new_member_poset<P>;

%enddef
