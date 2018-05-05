//
//  CSUndoManager.hpp
//  CppStep
//
//  Copyright © 2017-18 Jonathan Tanner. All rights reserved.
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

#include <functional>

class CSUndoManager {
public:
    CSUndoManager();

    void registerUndoFunc(std::function<void()> f);

    template<typename T>
    void registerUndoFuncArg(std::function<void(T)> f, T arg) {
        registerUndoFunc([f, arg]() { f(arg); });
    }

    template<typename S, typename T>
    void registerUndoFuncpArg2(void(*f)(S, T), S arg1, T arg2) {
        registerUndoFunc([f, arg1, arg2]() { f(arg1, arg2); });
    }

    template<typename T>
    void registerUndoTarget(T* target) {
        T value = *target;
        registerUndoFunc([target, value]() { *target = value; });
    }

    bool canUndo();
    void undo();
    bool canRedo();
    void redo();
private:
    class UndoItem {
    public:
        std::function<void()> f;
        UndoItem* next;
        UndoItem(std::function<void()> fTMP, UndoItem* nextTMP) {
            this->f = fTMP;
            this->next = nextTMP;
        }
        ~UndoItem() {
            delete this->next;
        }
    };

    UndoItem* undoStack;
    UndoItem* redoStack;

    bool isUndoing;
    bool isRedoing;
};


#endif /* CSUndoManager_hpp */
