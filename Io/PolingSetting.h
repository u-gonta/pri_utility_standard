#pragma once

#include "Common/Io/Setting.h"

namespace Standard
{
	namespace Io
	{
		namespace Poling
		{
			////////////////////////////////////////////////////////////////////////////////
			/// @class      CSetting
			/// @brief      IOの監視、IOの制御、状態を通知する設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CSetting
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CSetting()
				{
					Retry = 3;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CSetting& operator = (const CSetting& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CSetting()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CSetting& object)
				{
					this->Retry = object.Retry;
					this->Default = object.Default;
					this->Connect = object.Connect;
					this->Other = object.Other;
				}

			public:
				//! リトライ回数
				int Retry;

				//! Ioのデフォルトな設定クラス
				Setting::CDefault Default;

				//! Ioへ接続を行う設定クラス
				Setting::CConnect Connect;

				//! その他
				Variant::CManager Other;
			};
		}
	}
}