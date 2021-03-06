/* =========================================================== *
 * QSFML (c) Kamil Koczurek | koczurekk@gmail.com	       *
 * GNU GPL v3 License http://www.gnu.org/licenses/gpl-3.0.html *
 * =========================================================== */

#include "string.hpp"

namespace qsf
{
    String::String(sf::String str)
        : QString(str.toAnsiString().c_str())
    { }

    String String::arg(String str)
    {
        return String(static_cast<QString*>(this)->arg(str.toStdString().c_str()));
    }

    String::operator const sf::String()
    {
        return sf::String(this->toStdString());
    }
}
