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
#ifndef MG_CONSOLE_HPP
#define MG_CONSOLE_HPP

/**
 * @file     console.hpp
 * @brief    Generic Command Line text colouriser
 */

/**** System includes, namespaces, then local includes  ***********************/
#include <ostream>

/**** Definitions ************************************************************/

/**
 * Colourise the text on the stdout
 */
namespace mgbase::console
{
    enum Colour
    {
        // Low intensity text colours
        LO_RED     = 31,
        LO_GREEN   = 32,
        LO_YELLOW  = 33,
        LO_BLUE    = 34,
        LO_MAGENTA = 35,
        LO_CYAN    = 36,
        LO_WHITE   = 37,

        // High intensity text colours
        HI_RED     = 91,
        HI_GREEN   = 92,
        HI_YELLOW  = 93,
        HI_BLUE    = 94,
        HI_MAGENTA = 95,
        HI_CYAN    = 96,
        HI_WHITE   = 97,

        // Default console colours
        DEFAULT = 39
    };

    std::ostream& operator << (std::ostream& os, Colour colour );

    enum Background {
        // Background colours
        BG_RED     = 41,
        BG_GREEN   = 42,
        BG_YELLOW  = 43,
        BG_BLUE    = 44,
        BG_MAGENTA = 45,
        BG_CYAN    = 46,
        BG_WHITE   = 47
    };

    std::ostream& operator << (std::ostream& os, Background background );

    enum Reset {
        RESET = 0
    };

    std::ostream& operator << (std::ostream& os, Reset reset );

} // namespace mgbase::console

#endif /* MG_CONSOLE_HPP */