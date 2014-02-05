#
# Copyright (c) 2014 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Simple remote python server program

## NOTES:
##     Currently only handles interactive mode.
##     It is telnet aware in only a limited sense.
##
##     This version uses the standard python interpreter
##     without the sheaf modules being statically loaded
##     (They have to be "imported" to be used).

##$$TODO: Move to a more appropriate location.
##$$TODO: Design and implement "Request" and "Reply" message classes.
##$$TODO: Merge with server version which handles python scripts (files).
##$$TODO: Add history and logging capabilities.

import SocketServer
import code
import sys
import string
import StringIO

#import sheafmod
#import bundlemod
#import feamod

defaultHost = ''  # Local host
defaultPort = 12345
BUFSIZE = 1024

banner = """
#################################
# Sheaf interpreter version 0.1 #
#################################
"""

###############################################################################

class MyHandler(SocketServer.BaseRequestHandler):

    ###########################################################################

    def handle_line(self):
        line = ""
        while 1:       
            request = self.request.recv(BUFSIZE)

            ## Windows telnet uses character at a time
            ## so handle things like backspace.
            
            if len(request) == 1:
                if ord(request) == 8: # backspace
                    request = ""
                    if line != "": line = line[:-1]
                    
            line = line + request
            
            ##print line
            if line != "" and line[-1] == '\n':
                line = string.rstrip(line)  ## Strip off whitespace chars at end of line.
                break
            
        return line            

    ###########################################################################

    def handle(self):

        self.request.send(banner)

        ##$$TODO: Make more telnet aware.

        prompt_1 = ">>> " 
        prompt_2 = "... "
        self.request.send(prompt_1)
        while 1:

            line = self.handle_line() 
            ##print "***",line,"***"

            ## If client sends "quit", finish and close the connection.       
            if line == "quit":
                break;

            ## Redirect stdout and stderr.

            stdout = sys.stdout
	    stderr = sys.stderr
	    sys.stdout = sys.stderr = outerr = StringIO.StringIO()

            r = console.push(line);
 
            ## Set stdout and stderr back to the system objects.
            
            sys.stdout = stdout
            sys.stderr = stderr
            
            ##print "*** r =",r

            ## Strip off whitespace chars at end of line.
            reply = string.rstrip(outerr.getvalue())

            ##print reply
            
            self.request.send(reply)

            if r == 0:
                prompt = "\r\n" + prompt_1 # CR\LF is for windows
            else:
                prompt = prompt_2
                
            self.request.send(prompt)
          
        self.request.close()

###############################################################################

host = defaultHost
port = defaultPort
if len(sys.argv) == 2: port = int(sys.argv[1])

addr = (host, port)
console = code.InteractiveConsole()
server = SocketServer.ForkingTCPServer(addr, MyHandler)

print banner,
print "Serving on port", port
server.serve_forever()

    


