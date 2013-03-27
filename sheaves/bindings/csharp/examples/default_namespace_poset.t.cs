using System;
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
