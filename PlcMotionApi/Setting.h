#pragma once

namespace Standard
{
	namespace Plc
	{
		////////////////////////////////////////////////////////////////////////////////
		/// @class      CTemplate
		/// @brief      設定するテンプレートのクラス
		////////////////////////////////////////////////////////////////////////////////
		class CTemplate
		{
		public:
			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コンストラクタ
			////////////////////////////////////////////////////////////////////////////////
			CTemplate()
			{
				Name = "";
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コピー代入演算子
			/// @return			自クラス
			////////////////////////////////////////////////////////////////////////////////
			CTemplate& operator = (const CTemplate& object) noexcept
			{
				// 更新
				Update(object);

				return *this;
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			デストラクタ
			////////////////////////////////////////////////////////////////////////////////
			virtual ~CTemplate()
			{

			}

		protected:
			////////////////////////////////////////////////////////////////////////////////
			/// @brief			自クラスを更新
			/// @param[in]		object	自クラス
			////////////////////////////////////////////////////////////////////////////////
			void Update(const CTemplate& object)
			{
				this->Name = object.Name;
			}

		public:
			//! 機器の名前
			std::string Name;
		};
	}
}