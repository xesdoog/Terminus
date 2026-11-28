#include "LuaSettings.hpp"
#include "Lua/LuaMgr.hpp"
#include "game/frontend/Menu.hpp"

namespace Terminus::Submenus
{
	using namespace Terminus::LuaJIT;

	static std::shared_ptr<LuaModule> selectedModule{nullptr};
	static std::shared_ptr<LuaModule> dragSourcePtr{nullptr};
	static std::string selectedDisabledPath{};
	static std::string dragSourceStr{};

	static bool shouldDrawProperties = false;

	void RenderLuaSettings()
	{
		auto& modules         = LuaManager::GetModules();
		auto& disabledModules = LuaManager::GetDisabledModules();

		if (ImGui::Button("Reload All"))
			LuaManager::ReloadAllModules();
		ImGui::Spacing();

		auto region = ImGui::GetContentRegionAvail();

		ImGui::BeginChild("##enabledScripts", ImVec2(region.x * 0.5, 0), ImGuiChildFlags_Borders);
		ImGui::Text("Enabled Scripts");
		ImGui::Separator();

		for (auto& m : modules)
		{
			auto pathName = m->GetRoot().string();

			ImGui::PushID(&m);
			ImGui::BeginDisabled(dragSourcePtr && m == dragSourcePtr);
			bool isBroken = m->GetLoadState() == LuaModule::SUSPENDED;

			if (isBroken)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9, 0, 0, 1.0));
				ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(0.9, 0, 0, 0.5));
			}

			if (ImGui::Selectable(m->GetName().data(), (selectedModule && m == selectedModule)))
				selectedModule = m;

			if (isBroken)
				ImGui::PopStyleColor(2);

			ImGui::EndDisabled();
			ImGui::PopID();
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Right click to open the context menu or drag to move to the disabled list.");
				if (isBroken)
				{
					const std::string& err = m->GetErrorMsg();
					ImGui::SetTooltip(
					    std::format("Unloaded due to a malfunction: '{}'", err.empty() ? "Unknown error." : err).c_str());
				}
			}

			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				selectedModule = m;
				ImGui::OpenPopup(pathName.c_str());
			}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				dragSourcePtr = m;
				ImGui::SetDragDropPayload("ENABLED_MODULE", &m, sizeof(m));
				ImGui::Selectable(m->GetName().data(), true);
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
				ImGui::EndDragDropSource();
			}
			else
				dragSourcePtr = nullptr;

			if (ImGui::BeginPopup(pathName.c_str()))
			{
				if (ImGui::MenuItem("Reload"))
					m->Reload();

				if (ImGui::MenuItem("Disable"))
					m->Disable();

				if (ImGui::MenuItem("Properties"))
					shouldDrawProperties = true;

				ImGui::EndPopup();
			}
		}
		ImGui::EndChild();

		if (shouldDrawProperties && selectedModule)
		{
			shouldDrawProperties = false;
			ImGui::OpenPopup(selectedModule->GetName().data());
		}

		bool isOpen = true;
		ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImVec2(400, 800));
		if (selectedModule && ImGui::BeginPopupModal(selectedModule->GetName().data(), &isOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::BeginTable("##scriptInfo", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_RowBg))
			{
				auto meta = selectedModule->GetMetadata();
				ImGui::TableSetupColumn("#k", ImGuiTableColumnFlags_WidthFixed);
				ImGui::TableSetupColumn("#v", ImGuiTableColumnFlags_WidthStretch);
				ImGui::PushFont(Terminus::Menu::Font::g_OptionsFont);

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Author");
				ImGui::TableSetColumnIndex(1);
				ImGui::TextWrapped(meta.m_Author.c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Version");
				ImGui::TableSetColumnIndex(1);
				ImGui::TextWrapped(meta.m_Version.c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Description");
				ImGui::TableSetColumnIndex(1);
				ImGui::TextWrapped(meta.m_Description.c_str());

				ImGui::PopFont();
				ImGui::EndTable();
			}
			ImGui::EndPopup();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DISABLED_MODULE"))
			{
				const char* droppedPath = static_cast<const char*>(payload->Data);
				LuaManager::EnableModule(droppedPath);
				dragSourceStr = "";
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::SameLine();
		ImGui::BeginChild("##disabledScripts", ImVec2(), ImGuiChildFlags_Borders);
		ImGui::Text("Disabled Scripts");
		ImGui::Separator();
		for (auto& m : disabledModules)
		{
			auto pathName = m.m_Path.string();

			ImGui::PushID(&m);
			ImGui::BeginDisabled(pathName == dragSourceStr);
			if (ImGui::Selectable(m.m_Name.c_str(), pathName == selectedDisabledPath))
				selectedDisabledPath = pathName;
			ImGui::EndDisabled();
			ImGui::PopID();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Right click to open the context menu or drag to move to the enabled modules list.");

			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				selectedDisabledPath = pathName;
				ImGui::OpenPopup(pathName.c_str());
			}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				dragSourceStr = pathName;
				ImGui::SetDragDropPayload("DISABLED_MODULE", pathName.c_str(), pathName.size() + 1);
				ImGui::Selectable(m.m_Name.c_str(), true);
				ImGui::EndDragDropSource();
			}
			else
				dragSourceStr = "";

			if (ImGui::BeginPopup(pathName.c_str()))
			{
				if (ImGui::MenuItem("Enable"))
					LuaManager::EnableModule(pathName);

				ImGui::EndPopup();
			}
		}
		ImGui::EndChild();
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENABLED_MODULE"))
			{
				LuaModule* droppedModule = *static_cast<LuaModule**>(payload->Data);
				droppedModule->Disable();
				dragSourcePtr = nullptr;
			}
			ImGui::EndDragDropTarget();
		}
	}
}
