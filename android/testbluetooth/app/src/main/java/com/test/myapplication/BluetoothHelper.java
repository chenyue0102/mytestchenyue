package com.test.myapplication;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.ParcelUuid;
import android.os.Parcelable;

import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.UUID;


public class BluetoothHelper {
    public static final UUID MY_UUID = UUID.fromString("1a68fa50-a83b-11e3-9be7-425861b86ab6");

    public static final UUID BASE_UUID = UUID.fromString("00000000-0000-1000-8000-00805F9B34FB");
    public static final UUID SDP_PROTOCOL_UUID= UUID.fromString("00000001-0000-1000-8000-00805F9B34FB");
    public static final UUID UDP_PROTOCOL_UUID= UUID.fromString("00000002-0000-1000-8000-00805F9B34FB");
    public static final UUID RFCOMM_PROTOCOL_UUID      =UUID.fromString("00000003-0000-1000-8000-00805F9B34FB");
    public static final UUID TCP_PROTOCOL_UUID= UUID.fromString("00000004-0000-1000-8000-00805F9B34FB");
    public static final UUID TCSBIN_PROTOCOL_UUID      =UUID.fromString("00000005-0000-1000-8000-00805F9B34FB");
    public static final UUID TCSAT_PROTOCOL_UUID       =UUID.fromString("00000006-0000-1000-8000-00805F9B34FB");
    public static final UUID OBEX_PROTOCOL_UUID        =UUID.fromString("00000008-0000-1000-8000-00805F9B34FB");
    public static final UUID IP_PROTOCOL_UUID          =UUID.fromString("00000009-0000-1000-8000-00805F9B34FB");
    public static final UUID FTP_PROTOCOL_UUID= UUID.fromString("0000000A-0000-1000-8000-00805F9B34FB");
    public static final UUID HTTP_PROTOCOL_UUID        =UUID.fromString("0000000C-0000-1000-8000-00805F9B34FB");
    public static final UUID WSP_PROTOCOL_UUID= UUID.fromString("0000000E-0000-1000-8000-00805F9B34FB");
    public static final UUID BNEP_PROTOCOL_UUID        =UUID.fromString("0000000F-0000-1000-8000-00805F9B34FB");
    public static final UUID UPNP_PROTOCOL_UUID        =UUID.fromString("00000010-0000-1000-8000-00805F9B34FB");
    public static final UUID HID_PROTOCOL_UUID= UUID.fromString("00000011-0000-1000-8000-00805F9B34FB");
    public static final UUID HCCC_PROTOCOL_UUID        =UUID.fromString("00000012-0000-1000-8000-00805F9B34FB");
    public static final UUID HCDC_PROTOCOL_UUID        =UUID.fromString("00000014-0000-1000-8000-00805F9B34FB");
    public static final UUID HN_PROTOCOL_UUID          =UUID.fromString("00000016-0000-1000-8000-00805F9B34FB");
    public static final UUID AVCTP_PROTOCOL_UUID       =UUID.fromString("00000017-0000-1000-8000-00805F9B34FB");
    public static final UUID AVDTP_PROTOCOL_UUID       =UUID.fromString("00000019-0000-1000-8000-00805F9B34FB");
    public static final UUID CMPT_PROTOCOL_UUID        =UUID.fromString("0000001B-0000-1000-8000-00805F9B34FB");
    public static final UUID UDI_C_PLANE_PROTOCOL_UUID =UUID.fromString("0000001D-0000-1000-8000-00805F9B34FB");
    public static final UUID L2CAP_PROTOCOL_UUID       =UUID.fromString("00000100-0000-1000-8000-00805F9B34FB");

    public static final UUID ServiceDiscoveryServerServiceClassID_UUID       =UUID.fromString("00001000-0000-1000-8000-00805F9B34FB");
    public static final UUID BrowseGroupDescriptorServiceClassID_UUID        =UUID.fromString("00001001-0000-1000-8000-00805F9B34FB");
    public static final UUID PublicBrowseGroupServiceClass_UUID              =UUID.fromString("00001002-0000-1000-8000-00805F9B34FB");
    public static final UUID SerialPortServiceClass_UUID                     =UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    public static final UUID LANAccessUsingPPPServiceClass_UUID              =UUID.fromString("00001102-0000-1000-8000-00805F9B34FB");
    public static final UUID DialupNetworkingServiceClass_UUID               =UUID.fromString("00001103-0000-1000-8000-00805F9B34FB");
    public static final UUID IrMCSyncServiceClass_UUID                       =UUID.fromString("00001104-0000-1000-8000-00805F9B34FB");
    public static final UUID OBEXObjectPushServiceClass_UUID                 =UUID.fromString("00001105-0000-1000-8000-00805F9B34FB");
    public static final UUID OBEXFileTransferServiceClass_UUID               =UUID.fromString("00001106-0000-1000-8000-00805F9B34FB");
    public static final UUID IrMCSyncCommandServiceClass_UUID                =UUID.fromString("00001107-0000-1000-8000-00805F9B34FB");
    public static final UUID HeadsetServiceClass_UUID                        =UUID.fromString("00001108-0000-1000-8000-00805F9B34FB");
    public static final UUID CordlessTelephonyServiceClass_UUID              =UUID.fromString("00001109-0000-1000-8000-00805F9B34FB");
    public static final UUID AudioSourceServiceClass_UUID                    =UUID.fromString("0000110A-0000-1000-8000-00805F9B34FB");
    public static final UUID AudioSinkServiceClass_UUID                      =UUID.fromString("0000110B-0000-1000-8000-00805F9B34FB");
    public static final UUID AVRemoteControlTargetServiceClass_UUID          =UUID.fromString("0000110C-0000-1000-8000-00805F9B34FB");
    public static final UUID AdvancedAudioDistributionServiceClass_UUID      =UUID.fromString("0000110D-0000-1000-8000-00805F9B34FB");
    public static final UUID AVRemoteControlServiceClass_UUID                =UUID.fromString("0000110E-0000-1000-8000-00805F9B34FB");
    public static final UUID VideoConferencingServiceClass_UUID              =UUID.fromString("0000110F-0000-1000-8000-00805F9B34FB");
    public static final UUID IntercomServiceClass_UUID                       =UUID.fromString("00001110-0000-1000-8000-00805F9B34FB");
    public static final UUID FaxServiceClass_UUID                            =UUID.fromString("00001111-0000-1000-8000-00805F9B34FB");
    public static final UUID HeadsetAudioGatewayServiceClass_UUID            =UUID.fromString("00001112-0000-1000-8000-00805F9B34FB");
    public static final UUID WAPServiceClass_UUID                            =UUID.fromString("00001113-0000-1000-8000-00805F9B34FB");
    public static final UUID WAPClientServiceClass_UUID                      =UUID.fromString("00001114-0000-1000-8000-00805F9B34FB");
    public static final UUID PANUServiceClass_UUID                           =UUID.fromString("00001115-0000-1000-8000-00805F9B34FB");
    public static final UUID NAPServiceClass_UUID                            =UUID.fromString("00001116-0000-1000-8000-00805F9B34FB");
    public static final UUID GNServiceClass_UUID                             =UUID.fromString("00001117-0000-1000-8000-00805F9B34FB");
    public static final UUID DirectPrintingServiceClass_UUID                 =UUID.fromString("00001118-0000-1000-8000-00805F9B34FB");
    public static final UUID ReferencePrintingServiceClass_UUID              =UUID.fromString("00001119-0000-1000-8000-00805F9B34FB");
    public static final UUID ImagingServiceClass_UUID                        =UUID.fromString("0000111A-0000-1000-8000-00805F9B34FB");
    public static final UUID ImagingResponderServiceClass_UUID               =UUID.fromString("0000111B-0000-1000-8000-00805F9B34FB");
    public static final UUID ImagingAutomaticArchiveServiceClass_UUID        =UUID.fromString("0000111C-0000-1000-8000-00805F9B34FB");
    public static final UUID ImagingReferenceObjectsServiceClass_UUID        =UUID.fromString("0000111D-0000-1000-8000-00805F9B34FB");
    public static final UUID HandsfreeServiceClass_UUID                      =UUID.fromString("0000111E-0000-1000-8000-00805F9B34FB");
    public static final UUID HandsfreeAudioGatewayServiceClass_UUID          =UUID.fromString("0000111F-0000-1000-8000-00805F9B34FB");
    public static final UUID DirectPrintingReferenceObjectsServiceClass_UUID =UUID.fromString("00001120-0000-1000-8000-00805F9B34FB");
    public static final UUID ReflectedUIServiceClass_UUID                    =UUID.fromString("00001121-0000-1000-8000-00805F9B34FB");
    public static final UUID BasicPringingServiceClass_UUID                  =UUID.fromString("00001122-0000-1000-8000-00805F9B34FB");
    public static final UUID PrintingStatusServiceClass_UUID                 =UUID.fromString("00001123-0000-1000-8000-00805F9B34FB");
    public static final UUID HumanInterfaceDeviceServiceClass_UUID           =UUID.fromString("00001124-0000-1000-8000-00805F9B34FB");
    public static final UUID HardcopyCableReplacementServiceClass_UUID       =UUID.fromString("00001125-0000-1000-8000-00805F9B34FB");
    public static final UUID HCRPrintServiceClass_UUID                       =UUID.fromString("00001126-0000-1000-8000-00805F9B34FB");
    public static final UUID HCRScanServiceClass_UUID                        =UUID.fromString("00001127-0000-1000-8000-00805F9B34FB");
    public static final UUID CommonISDNAccessServiceClass_UUID               =UUID.fromString("00001128-0000-1000-8000-00805F9B34FB");
    public static final UUID VideoConferencingGWServiceClass_UUID            =UUID.fromString("00001129-0000-1000-8000-00805F9B34FB");
    public static final UUID UDIMTServiceClass_UUID                          =UUID.fromString("0000112A-0000-1000-8000-00805F9B34FB");
    public static final UUID UDITAServiceClass_UUID                          =UUID.fromString("0000112B-0000-1000-8000-00805F9B34FB");
    public static final UUID AudioVideoServiceClass_UUID                     =UUID.fromString("0000112C-0000-1000-8000-00805F9B34FB");
    public static final UUID PnPInformationServiceClass_UUID                 =UUID.fromString("00001200-0000-1000-8000-00805F9B34FB");
    public static final UUID GenericNetworkingServiceClass_UUID              =UUID.fromString("00001201-0000-1000-8000-00805F9B34FB");
    public static final UUID GenericFileTransferServiceClass_UUID            =UUID.fromString("00001202-0000-1000-8000-00805F9B34FB");
    public static final UUID GenericAudioServiceClass_UUID                   =UUID.fromString("00001203-0000-1000-8000-00805F9B34FB");
    public static final UUID GenericTelephonyServiceClass_UUID               =UUID.fromString("00001204-0000-1000-8000-00805F9B34FB");
    public static final UUID UPnPServiceClass_UUID                           =UUID.fromString("00001205-0000-1000-8000-00805F9B34FB");
    public static final UUID UPnPIpServiceClass_UUID                         =UUID.fromString("00001206-0000-1000-8000-00805F9B34FB");
    public static final UUID ESdpUPnPIpPanServiceClass_UUID                  =UUID.fromString("00001300-0000-1000-8000-00805F9B34FB");
    public static final UUID ESdpUPnPIpLapServiceClass_UUID                  =UUID.fromString("00001301-0000-1000-8000-00805F9B34FB");
    public static final UUID EdpUPnpIpL2CAPServiceClass_UUID                 =UUID.fromString("00001302-0000-1000-8000-00805F9B34FB");

    private static final String TAG = "BluetoothHelper";
    private BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    private BluetoothReceiver mBluetoothReceiver = null;
    private BluetoothHelperCallback mBluetoothHelperCallback = null;
    private Context mContext = null;

    public interface BluetoothHelperCallback{
        void onDiscoveryStarted();
        void onDiscoveryFinished();
        void onBluetoothDeviceFound(BluetoothDevice device);
        void onBluetoothDeviceUUIDResult(BluetoothDevice device, ParcelUuid[]uuids);
        void onBluetoothDeviceConnect(BluetoothDevice device, BluetoothSocket bluetoothSocket);
        void onBluetoothDeviceBondStateChanged(BluetoothDevice device, int bondState, int previousBondState, int reason);
    }


    public BluetoothHelper(Context context, BluetoothHelperCallback bluetoothHelperCallback){
        mContext = context;
        mBluetoothHelperCallback = bluetoothHelperCallback;
    }

    public boolean isBluetoothAvalidable(){
        return null != mBluetoothAdapter;
    }

    public boolean isEnabled(){
        return isBluetoothAvalidable() && mBluetoothAdapter.isEnabled();
    }

    public boolean enable(){
        return isBluetoothAvalidable() && mBluetoothAdapter.enable();
    }

    public static boolean setScanMode(BluetoothAdapter bluetoothAdapter, int mode, long durationMillis){
        boolean success = false;
        try {
            Class clazz = bluetoothAdapter.getClass();
            Method method = clazz.getMethod("setScanMode", int.class, int.class);
            Object object = method.invoke(bluetoothAdapter, mode, (int)durationMillis);
            if (object instanceof Boolean){
                success = (Boolean)object;
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return success;
    }

    public boolean setScanMode(int mode, long durationMillis){
        return isBluetoothAvalidable() && setScanMode(mBluetoothAdapter, mode, durationMillis);
    }

    public boolean startDiscovery(){
        if (null == mBluetoothReceiver){
            mBluetoothReceiver = new BluetoothReceiver(mBluetoothHelperCallback);
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
            intentFilter.addAction(BluetoothDevice.ACTION_UUID);
            intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
            intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
            mContext.registerReceiver(mBluetoothReceiver, intentFilter);
        }
        return isBluetoothAvalidable() && mBluetoothAdapter.startDiscovery();
    }

    public boolean fetchUuidsWithSdp(BluetoothDevice device){
        return device.fetchUuidsWithSdp();
    }

    public boolean createBond(BluetoothDevice device){
        return device.createBond();
    }

    public boolean cancelDiscovery(){
        if (null != mBluetoothReceiver){
            mContext.unregisterReceiver(mBluetoothReceiver);
            mBluetoothReceiver = null;
        }
        return isBluetoothAvalidable() && mBluetoothAdapter.cancelDiscovery();
    }

    public void connect(BluetoothDevice device, UUID uuid){
        new Thread(()->{
            try{
                BluetoothProfile d;

                String name = device.getName();
                BluetoothSocket bluetoothSocket = device.createRfcommSocketToServiceRecord(uuid);
                //BluetoothSocket bluetoothSocket = device.createInsecureRfcommSocketToServiceRecord(uuid);
                //BluetoothSocket bluetoothSocket = device.createRfcommSocket(1);
                InputStream inputStream = bluetoothSocket.getInputStream();
                OutputStream outputStream = bluetoothSocket.getOutputStream();
                bluetoothSocket.connect();
                if (null != mBluetoothHelperCallback){
                    mBluetoothHelperCallback.onBluetoothDeviceConnect(device, bluetoothSocket);
                }
            }catch (Exception e){
                e.printStackTrace();
            }
        }).start();
    }



    public static class BluetoothReceiver extends BroadcastReceiver{
        private BluetoothHelperCallback mBluetoothHelperCallback;

        public BluetoothReceiver(BluetoothHelperCallback callback){
            mBluetoothHelperCallback = callback;
        }
        @Override
        public void onReceive(Context context, Intent intent) {
            if (null == mBluetoothHelperCallback){
                return;
            }
            String action = intent.getAction();
            if (BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(action)){
                mBluetoothHelperCallback.onDiscoveryStarted();
            }else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)){
                mBluetoothHelperCallback.onDiscoveryFinished();
            }else if (BluetoothDevice.ACTION_FOUND.equals(action)){
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                if (null != device){
                    mBluetoothHelperCallback.onBluetoothDeviceFound(device);
                }
            }else if (BluetoothDevice.ACTION_UUID.equals(action)){
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                if (null != device) {
                    Parcelable[] uuidExtra = intent.getParcelableArrayExtra(BluetoothDevice.EXTRA_UUID);
                    ArrayList<ParcelUuid> parcelUuids = new ArrayList<>();
                    if (null != uuidExtra) {
                        for (Parcelable uuid : uuidExtra) {
                            if (uuid instanceof ParcelUuid) {
                                parcelUuids.add((ParcelUuid) uuid);
                            }
                        }
                    }
                    ParcelUuid tmp[] = new ParcelUuid[parcelUuids.size()];
                    parcelUuids.toArray(tmp);
                    mBluetoothHelperCallback.onBluetoothDeviceUUIDResult(device, tmp);
                }
            }else if (BluetoothDevice.ACTION_BOND_STATE_CHANGED.equals(action)){
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                int bondState = intent.getIntExtra(BluetoothDevice.EXTRA_BOND_STATE, BluetoothDevice.BOND_NONE);
                int previousBondState = intent.getIntExtra(BluetoothDevice.EXTRA_PREVIOUS_BOND_STATE, BluetoothDevice.BOND_NONE);
                int reason = 0;
                if (BluetoothDevice.BOND_NONE == bondState){
                    reason = intent.getIntExtra("android.bluetooth.device.extra.REASON", 0);
                }
                if (null != device){
                    mBluetoothHelperCallback.onBluetoothDeviceBondStateChanged(device, bondState, previousBondState, reason);
                }
            }
        }
    }
}
