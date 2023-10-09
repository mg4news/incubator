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
 * \file     idempotent.cpp
 * \author   mg4news
 * \date     2023-09-20
 *
 * \brief
 * Idempotent initialisation utility class.
 */

/**** System includes, namespaces, then local includes  ***********************/
#include "mgbase/console.hpp"


/**** Definitions ************************************************************/

/**** Macros ****************************************************************/

/**** Local function prototypes (NB Use static modifier) ********************/

/**** Method implementations ************************************************/
namespace mgbase::console
{

// Overrides the << operator
std::ostream& operator << (std::ostream& os, Colour colour )
{
    return os << "\33[" << static_cast<int>(colour) << "m";
}
// <<

std::ostream& operator << (std::ostream& os, Background background )
{
    return os << "\33[" << static_cast<int>(background) << "m";
}
// <<

std::ostream& operator << (std::ostream& os, Reset reset )
{
    return os << "\33[" << static_cast<int>(reset) << "m";
}
// <<


} // namespace mgbase::console