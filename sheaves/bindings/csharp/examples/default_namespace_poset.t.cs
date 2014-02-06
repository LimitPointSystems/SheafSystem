
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

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace sheaf
{
    class default_namespace_poset
    {
        static void Main(string[] args)
        {
            // Construct the default namespace poset.

            namespace_poset lns = new namespace_poset("default_namespace_poset");

            // Write the namespace out to the console.

            System.Console.Write(lns.to_string());

            // Write the namespace out to a file.

            lns.get_read_write_access();

            storage_agent sa = new storage_agent("default_namespace_poset.t.hdf", sheaf_file.access_mode.READ_WRITE);
            sa.put_member_record_buffer_ub(15);
            sa.put_dof_tuple_record_size(128);
            sa.put_dof_tuple_record_buffer_ub(8);
            sa.write_entire(lns);
        }
    }
}
