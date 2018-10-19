//
//  CSUndoManager.hpp
//  CppStep
//
//  Copyright � 2018 Jonathan Tanner. All rights reserved.
//
//This file is part of CppStep.
//
//CppStep is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//CppStep is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with CppStep.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CSUndoManager_hpp
#define CSUndoManager_hpp

#include "CSCore.hpp"
#include "CSMenu.hpp"

#if defined(CS_Mac)
#define CSNSUndoManager
#endif

#include <functional>

#ifdef CSNSUndoManager
#import <Foundation/Foundation.h>
#endif

/** An undo manager */
class CSUndoManager {
public:
#ifdef CSNSUndoManager
    /** Create a CSUndoManager */
    CSUndoManager(NSUndoManager* nativeUndoManager);

    /** Create a CSUndoManager */
    CSUndoManager();
#endif

    /** Register an undo to the stack
      * @param f The function that will perform the undo
      */
    void registerUndoFunc(std::function<void()> f);

    /** Register an undo to the stack that restores the value of the given target
      * @param target The target whose value is to be restored
      */
    template<typename T>
    void registerUndoTarget(T* target) {
        T value = *target;
        registerUndoFunc([target, value]() { *target = value; });
    }

    bool canUndo(); /**< Get if there is an undo on the stack */
    void undo(); /**< Undo the last value from the undo stack */
    bool canRedo(); /**< Get if there is a redo on the stack */
    void redo(); /**< Redo the last value from the redo stack */
    
    CSMenuItem* undoMenuItem(CSKeyCode keyCode = CSKeyCode());
    CSMenuItem* redoMenuItem(CSKeyCode keyCode = CSKeyCode());
private:
#ifdef CSNSUndoManager
    NSUndoManager* nativeUndoManager;
#else
    /** An event that can be undone */
    class UndoItem {
    public:
        std::function<void()> f; /**< The function to be used to undo the event */
        UndoItem* next; /**< The next event to undo */
        /** Construct an event with the given function and next event */
        UndoItem(std::function<void()> fTMP, UndoItem* nextTMP) {
            this->f = fTMP;
            this->next = nextTMP;
        }
        /** Destruct the event and next event */
        ~UndoItem() {
            delete this->next;
        }
    };

    UndoItem* undoStack = nullptr; /**< The stack of undos */
    UndoItem* redoStack = nullptr; /**< The stack of redos */

    bool isUndoing = false; /**< Is undoing an event. While undoing a new event registered is a redo. */
    bool isRedoing = false; /**< Is redoing an event. While redoing a new event registered should not clear the redo stack. */
#endif
};


#endif /* CSUndoManager_hpp */
