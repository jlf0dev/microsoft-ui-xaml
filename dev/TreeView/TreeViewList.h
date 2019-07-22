﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ViewModel.h"

#include "TreeViewList.g.h"

class TreeViewList :
    public ReferenceTracker<TreeViewList, winrt::implementation::TreeViewListT>
{
public:
    TreeViewList();

    void OnDragItemsStarting(const winrt::IInspectable& sender, const winrt::DragItemsStartingEventArgs& args);
    void OnDragItemsCompleted(const winrt::IInspectable& sender, const winrt::DragItemsCompletedEventArgs& args);
    void OnContainerContentChanging(const winrt::IInspectable& sender, const winrt::ContainerContentChangingEventArgs& args);

    // IControlOverrides
    void OnDrop(winrt::DragEventArgs const& e);
    void OnDragOver(winrt::DragEventArgs const& e);
    void OnDragEnter(winrt::DragEventArgs const& e);
    void OnDragLeave(winrt::DragEventArgs const& e);

    // IItemsControlOverrides
    void PrepareContainerForItemOverride(winrt::DependencyObject const& element, winrt::IInspectable const& item);
    winrt::DependencyObject GetContainerForItemOverride();

    // IFrameworkElementOverrides
    void OnApplyTemplate();

    // IUIElementOverrides
    winrt::AutomationPeer OnCreateAutomationPeer();

    winrt::hstring GetDropTargetDropEffect();
    void SetDraggedOverItem(winrt::TreeViewItem newDraggedOverItem);
    void UpdateDropTargetDropEffect(bool forceUpdate, bool isLeaving, winrt::TreeViewItem keyboardReorderedContainer);    
    void EnableMultiselect(bool isEnabled);
    [[nodiscard]] bool IsMultiselect() const;

    [[nodiscard]] bool IsMutiSelectWithSelectedItems() const;
    [[nodiscard]] bool IsSelected(const winrt::TreeViewNode& node) const;
    std::vector<winrt::TreeViewNode> [[nodiscard]] GetRootsOfSelectedSubtrees() const;
    [[nodiscard]] int FlatIndex(const winrt::TreeViewNode& node) const;
    [[nodiscard]] bool IsFlatIndexValid(int index) const;
    unsigned int RemoveNodeFromParent(const winrt::TreeViewNode& node);
    winrt::TreeViewNode NodeFromContainer(winrt::DependencyObject const& container);
    winrt::DependencyObject ContainerFromNode(winrt::TreeViewNode const& node);
    [[nodiscard]] com_ptr<ViewModel> ListViewModel() const;
    void ListViewModel(com_ptr<ViewModel> viewModel);
    winrt::TreeViewNode DraggedTreeViewNode();
    void DraggedTreeViewNode(winrt::TreeViewNode const& node);

private:
    bool IsIndexValid(int index);
    hstring GetAutomationName(int index);
    hstring BuildEffectString(hstring priorString, hstring afterString, hstring dragString, hstring dragOverString);
    unsigned int IndexInParent(const winrt::TreeViewNode& node);
    [[nodiscard]] winrt::TreeViewNode NodeAtFlatIndex(int index) const;
    [[nodiscard]] winrt::TreeViewNode GetRootOfSelection(const winrt::TreeViewNode& node) const;
    void MoveNodeInto(winrt::TreeViewNode const& node, winrt::TreeViewNode const& insertAtNode);

    tracker_ref<winrt::TreeViewItem> m_draggedOverItem{ this };
    winrt::hstring m_dropTargetDropEffectString;
    int m_emptySlotIndex{ 0 };
    bool m_itemsSourceAttached{ false };
    bool m_isMultiselectEnabled{ false };
    tracker_com_ref<ViewModel> m_viewModel{ this };
    tracker_ref<winrt::TreeViewNode> m_draggedTreeViewNode{ this };
};

