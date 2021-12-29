#pragma once

#include <map>

#include "Common/Variant/Basis.h"
#include "Common/Signal/Define.h"

namespace Standard
{
	namespace Axis
	{
		namespace Setting
		{
			////////////////////////////////////////////////////////////////////////////////
			/// @class      CDefault
			/// @brief      軸のデフォルトな設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CDefault
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CDefault()
				{
					Timeout = 5000;
					Cycle = 10;
					Retry = 3;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CDefault& operator = (const CDefault& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CDefault()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CDefault& object)
				{
					this->Timeout = object.Timeout;
					this->Cycle = object.Cycle;
					this->Retry = object.Retry;
					this->Other = object.Other;
				}

			public:
				//! タイムアウト[ms]
				int Timeout;

				//! ポーリングの周期[ms]
				int Cycle;

				//! リトライ回数
				int Retry;

				//! その他
				Variant::CManager Other;
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @class      CDriver
			/// @brief      機器の設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CDriver
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CDriver()
				{
					Name = "";
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CDriver& operator = (const CDriver& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CDriver()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CDriver& object)
				{
					this->Name = object.Name;
					this->Other = object.Other;
				}

			public:
				//! ドライバの名前
				std::string Name;

				//! その他
				Variant::CManager Other;
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @class      CConnect
			/// @brief      軸に接続する設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CConnect
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CConnect()
				{

				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CConnect& operator = (const CConnect& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CConnect()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CConnect& object)
				{
					this->Drivers = object.Drivers;
					this->Other = object.Other;
				}

			public:
				//! 機器の設定クラス
				std::map<int, CDriver> Drivers;

				//! その他
				Variant::CManager Other;
			};
		}
	}
}
