#ifndef LFW_CORE_DEFINES_IDIALOG_INFO_HPP
#define LFW_CORE_DEFINES_IDIALOG_INFO_HPP

#include <optional>
#include <string>

#include "lfw-core/base/Fields.hpp"

/// IDialogInfo — 对话框信息
struct IDialogInfo
{
  std::optional<std::string> type;
  std::optional<std::string> fighter;
  std::optional<bool> pause;
  std::string i18n;
  std::optional<std::string> close_by;
};

inline const auto &dialog_info_fields()
{
  static const auto fs = fields<IDialogInfo>(
      field("type", FieldKind::Str, &IDialogInfo::type, "位置"),
      field("fighter", FieldKind::Str, &IDialogInfo::fighter, "说话者"),
      field("pause", FieldKind::Bool, &IDialogInfo::pause, "暂停"),
      field("i18n", FieldKind::Str, &IDialogInfo::i18n, "文本"),
      field("close_by", FieldKind::Str, &IDialogInfo::close_by, "关闭方式"));
  return fs;
}

#endif
