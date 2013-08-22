
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

// Interface for class EQUIVALENCE

#ifndef EQUIVALENCE_H
#define EQUIVALENCE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifdef PARALLEL_MPI

#ifndef STD_HDF5_H
#include "std_hdf5.h"
#endif

#include "mpi.h"

namespace sheaf
{

class poset_storage;
class poset;
  
class SHEAF_DLL_SPEC equivalence
{

  friend class poset_storage;

public:

  typedef struct
  {
    int      local_index;
    int      remote_index;
    int      remote_proc;
  }
  hdf_rep;

  typedef struct
  {
    int       remote_index;
    int       remote_proc;
    MPI_Aint  remote_storage;
  }
  mpi_rep;

  // queries:

  bool                 invariant() const;
  static MPI_Datatype  mpi_type();
  static hid_t         hdf_type();
  void                 make_hdf_rep(hdf_rep *xhdf_rep, int xlocal_index);
  void                 make_mpi_rep(mpi_rep *xmpi_rep);
  int                  remote_index();
  int                  remote_proc();
  poset_storage       *remote_storage();

  // actions:

  // constructors:

  equivalence(int xremote_index, int xremote_proc, poset_storage *xremote_storage);
  ~equivalence();

private:

  // data:

  int            _remote_index;    // index of sibling on other processor
  int            _remote_proc;     // processor where sibling is stored
  poset_storage *_remote_storage;  // address of remote poset_storage object

  // actions:

  void  put_remote_storage(poset_storage *xstorage);

  // constructors:

  equivalence(hdf_rep *xrep);

};

} // namespace sheaf

#endif // PARALLEL_MPI

#endif // ifndef EQUIVALENCE_H
