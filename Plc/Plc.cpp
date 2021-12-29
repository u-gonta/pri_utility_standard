#include "pch.h"

#include "Plc.h"
#include "Common/Version/Manager.h"
#include "Worker.h"

namespace Standard
{
	namespace Plc
	{
		//! Plcの制御を行うクラス
		static Worker::CTemplate _device;

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			バージョンのクラスを取得
		////////////////////////////////////////////////////////////////////////////////
		PLC_API Version::CObject GetVersion()
		{
			Version::CObject ret;

			Version::CManager& versionManager = Version::CManager::Instance();

			// バージョンのクラスを取得
			ret = versionManager.GetVersion();

			return ret;
		}

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			例外を通知する関数の登録
		/// @detail			例外の発生時に呼び出されたい関数を指定する
		/// @param[in]		object	呼び出されたい関数
		////////////////////////////////////////////////////////////////////////////////
		PLC_API void AttachFunctionException(std::function<void(const Exception::CObject&)> object)
		{
			// 例外を通知する関数の登録
			_device.AttachFunctionException(object);
		}

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			例外を通知する関数の解除
		/// @detail			例外の発生時に呼び出される関数を解除する
		////////////////////////////////////////////////////////////////////////////////
		PLC_API void DetachFunctionException()
		{
			// 例外を通知する関数の解除
			_device.DetachFunctionException();
		}

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			初期化
		/// @param[in]		object	デフォルトの設定クラス
		////////////////////////////////////////////////////////////////////////////////
		PLC_API void Initialize(const Setting::CDefault& object)
		{
			// 初期化
			_device.Initialize(object);
		}

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			破棄
		////////////////////////////////////////////////////////////////////////////////
		PLC_API void Destroy()
		{
			// 破棄
			_device.Destroy();
		}

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			接続
		/// @param[in]		object	接続の設定クラス
		////////////////////////////////////////////////////////////////////////////////
		PLC_API void Connect(const Setting::CConnect& object)
		{
			// 接続
			_device.Connect(object);
		}

		////////////////////////////////////////////////////////////////////////////////
		/// @brief			切断
		////////////////////////////////////////////////////////////////////////////////
		PLC_API void Disconnect()
		{
			// 切断
			_device.Disconnect();
		}
	}
}