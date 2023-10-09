//=============================================================================
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any means.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// This is a simplified version of UNLICENSE. For more information,
// please refer to <http://unlicense.org/>
//=============================================================================

/**
 * \file     version.cpp
 * \author   mg4news
 * \date     2023-09-20
 *
 * \brief
 * Versioning utilities
 */

/**** System includes, namespaces, then local includes  ***********************/
#include "mgbase/base.hpp"


/**** Definitions ************************************************************/

/**** Macros ****************************************************************/

/**** Local function prototypes (NB Use static modifier) ********************/

/**** Method implementations ************************************************/
std::string mgbase::version() {return MGBASE_VERSION;}
int         mgbase::version_major() {return MGBASE_VERSION_MAJOR;}
int         mgbase::version_minor() {return MGBASE_VERSION_MINOR;}
int         mgbase::version_patch() {return MGBASE_VERSION_PATCH;}
