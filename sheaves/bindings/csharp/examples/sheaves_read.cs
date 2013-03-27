using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace sheaf
{
    class sheaves_read
    {
        static void Main(string[] args)
        {
            // Read the filename.

            String filename;

            if(args.Length > 0)
            {
                filename = args[0];
            }
            else
            {
                System.Console.Write("usage: sheaves_read sheaf_file [enable_error_report]");
                return;
            }

            bool lenable_error_report = (args.Length > 1);

            /// @hack prototype instantiation bug.

            namespace_poset.initialize_prototypes();

            // Make the default namespace

            namespace_poset ns = new namespace_poset("test");

            // Read the namespace from the file;
            // need write access in order to read it.

            ns.get_read_write_access();
            storage_agent sa = new storage_agent(filename, sheaf_file.access_mode.READ_ONLY, false, lenable_error_report);
            sa.put_member_record_buffer_ub(15);

            sa.read_entire(ns);

            // Output a text version to stdout

            System.Console.Write(ns.to_string());
        }
    }
}
