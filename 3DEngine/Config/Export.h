//==========================================================
// Export.h
//
// D�finition de macros d'exportation
//
//==========================================================

#ifndef EXPORT_H
#define EXPORT_H

namespace Yes
{
    //==========================================================
    // Macro d'exportation / importation
    //==========================================================
    #ifdef YESENGINE_EXPORTS
    #   define YES_EXPORT __declspec(dllimport)
    #else
    #   define YES_EXPORT __declspec(dllexport)
    #endif

    //==========================================================
    // D�sactivation du warning 4251
    // "T1 n�cessite une interface DLL pour �tre utilis�(e) par
    // les clients de class T2" 
    //==========================================================
    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #endif

} // namespace Yes


#endif // EXPORT_H
