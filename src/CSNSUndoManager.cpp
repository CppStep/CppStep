//
//  CSNSUndoManager.cpp
//  VDJartnet
//
//  Created by Jonathan Tanner on 28/09/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#include "CSUndoManager.hpp"

#ifdef CSNSUndoManager

CSUndoManager::CSUndoManager(NSUndoManager* nativeUndoManager) : nativeUndoManager(nativeUndoManager) {}

CSUndoManager::CSUndoManager() : CSUndoManager([[NSUndoManager alloc] init]) {}

void CSUndoManager::registerUndoFunc(std::function<void()> f) {
    [nativeUndoManager registerUndoWithTarget:nativeUndoManager handler:^(id _){ f(); }];
}

bool CSUndoManager::canUndo() {
    return [nativeUndoManager canUndo];
}

void CSUndoManager::undo() {
    [nativeUndoManager undo];
}

bool CSUndoManager::canRedo() {
    return [nativeUndoManager canRedo];
}

void CSUndoManager::redo() {
    [nativeUndoManager redo];
}

CSMenuItem* CSUndoManager::undoMenuItem(CSKeyCode keyCode) {
    auto nKeyCode = keyCode.toNativeKeyCode();
    NSMenuItem* menuItem = [[NSMenuItem alloc] initWithTitle:[nativeUndoManager undoMenuItemTitle] action:@selector(undo) keyEquivalent:nKeyCode.first];
    [menuItem setTarget:nativeUndoManager];
    [menuItem setKeyEquivalentModifierMask:NSEventModifierFlagCommand/*nKeyCode.second*/];
    return new CSMenuItem(menuItem);
}

CSMenuItem* CSUndoManager::redoMenuItem(CSKeyCode keyCode) {
    auto nKeyCode = keyCode.toNativeKeyCode();
    NSMenuItem* menuItem = [[NSMenuItem alloc] initWithTitle:[nativeUndoManager redoMenuItemTitle] action:@selector(redo) keyEquivalent:nKeyCode.first];
    [menuItem setTarget:nativeUndoManager];
    [menuItem setKeyEquivalentModifierMask:NSEventModifierFlagCommand/*nKeyCode.second*/];
    return new CSMenuItem(menuItem);
}

#endif
