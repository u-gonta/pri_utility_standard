#pragma once

#include "Common/Variant/Basis.h"
#include "Common/Io/Status.h"

namespace Standard
{
	namespace Io
	{
		namespace Setting
		{
			////////////////////////////////////////////////////////////////////////////////
			/// @class      CAddressRange
			/// @brief      アドレスの範囲クラス
			////////////////////////////////////////////////////////////////////////////////
			class CAddressRange
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CAddressRange()
				{
					Size = 0;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CAddressRange& operator = (const CAddressRange& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CAddressRange()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CAddressRange& object)
				{
					this->Start = object.Start;
					this->Size = object.Size;
				}

			public:
				//! アドレスのクラス(先頭のアドレス)
				Specify::CAddress Start;

				//! データ数
				int Size;
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @class      CDefault
			/// @brief      Ioのデフォルトな設定クラス
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
			/// @class      CConnect
			/// @brief      Ioに接続する設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CConnect
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CConnect()
				{
					Identifier = "";
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

			private:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CConnect& object)
				{
					this->Identifier = object.Identifier;
					this->AddressRanges.clear();
					std::copy(object.AddressRanges.begin(), object.AddressRanges.end(), std::back_inserter(this->AddressRanges));
					this->Other = object.Other;
				}

			public:
				//! 機器の識別子
				std::string Identifier;

				//! 読み込むアドレスの範囲
				std::vector<CAddressRange> AddressRanges;

				//! その他
				Variant::CManager Other;
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @class      CInput
			/// @brief      入力の設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CInput
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CInput()
				{

				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CInput& operator = (const CInput& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CInput()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CInput& object)
				{
					this->Addresses.clear();
					std::copy(object.Addresses.begin(), object.Addresses.end(), std::back_inserter(this->Addresses));
				}

			public:
				//! 読み込むアドレス
				std::vector<Specify::CAddress> Addresses;
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @class      CTrigger
			/// @brief      トリガーの設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CTrigger
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CTrigger()
				{
					Direction = Status::DirectionRise;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CTrigger& operator = (const CTrigger& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				virtual ~CTrigger()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CTrigger& object)
				{
					this->Address = object.Address;
					this->Direction = object.Direction;
				}

			public:
				//! アドレス
				Specify::CAddress Address;

				//! ビットの方向
				Status::EnumDirection Direction;
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @class      CInputPending
			/// @brief      IOの入力が変化するのを待つ設定クラス
			////////////////////////////////////////////////////////////////////////////////
			class CInputPending
			{
			public:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コンストラクタ
				////////////////////////////////////////////////////////////////////////////////
				CInputPending()
				{
					Timeout = 3000;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			コピー代入演算子
				/// @return			自クラス
				////////////////////////////////////////////////////////////////////////////////
				CInputPending& operator = (const CInputPending& object) noexcept
				{
					// 更新
					Update(object);

					return *this;
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @brief			デストラクタ
				////////////////////////////////////////////////////////////////////////////////
				~CInputPending()
				{

				}

			protected:
				////////////////////////////////////////////////////////////////////////////////
				/// @brief			自クラスを更新
				/// @param[in]		object	自クラス
				////////////////////////////////////////////////////////////////////////////////
				void Update(const CInputPending& object)
				{
					this->Trigger = object.Trigger;
					this->Timeout = object.Timeout;
					this->Other = object.Other;
				}

			public:
				//! トリガーの設定クラス
				CTrigger Trigger;

				//! タイムアウト[ms]
				int Timeout;

				//! その他
				Variant::CManager Other;
			};
		}
	}
}