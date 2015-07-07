//==========================================================
// Export.h
//
// Définition de macros d'exportation
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
    #   define YES_EXPORT __declspec(dllexport)
    #else
    #   define YES_EXPORT __declspec(dllimport)
    #endif

    //==========================================================
    // Désactivation du warning 4251
    // "T1 nécessite une interface DLL pour être utilisé(e) par
    // les clients de class T2" 
    //==========================================================
    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #endif

} // namespace Yes


#endif // EXPORT_H
