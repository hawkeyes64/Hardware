package com.example.jes_pc.arducoptercontroller;

/** Android objects **/
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

/** Container Objects **/
import java.util.ArrayList;
import java.util.Set;

/** Android Widget Headers **/
import android.view.View;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

/** Bluetooth Objects **/
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;

public class DeviceList extends AppCompatActivity {
    /**********************************************************
     * Android Widgets
     * btnPaired    - button to trigger device pairing
     * ListView     - List container for all bluetooth devices
     *********************************************************/
    Button btnPaired;
    ListView deviceList;

    /**********************************************************
     * Bluetooth Related objects
     * myBluetooth      - Variable to determine if the
     *  smartphone has a bluetooth sensor
     * pairedDevices    - bluethoot devices that the phone's
     *  bluetooth sensor was able to detect
     * EXTRA_ADDRESS    -
     *********************************************************/
    private BluetoothAdapter myBluetooth;
    private Set<BluetoothDevice> pairedDevices;
    public static String EXTRA_ADDRESS = "device_address";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_list);

        /** Calling the widgets **/
        btnPaired = (Button)findViewById(R.id.btnPairedDevices);
        deviceList = (ListView)findViewById(R.id.listViewPairedDevices);

        /** block to determine if the device has a bluetooth adapter **/
        if(myBluetooth == null){
            /** Show message that the smartphone device has no bluetooth adapter **/
            Toast.makeText(getApplicationContext(),
                    "Bluetooth device not available",
                    Toast.LENGTH_LONG);

            /** Terminate the App **/
            finish();
        }

        /** Bluetooth adapter exist but not enabled **/
        else if(!myBluetooth.isEnabled()){
            /** Prompt the user to activate the bluetooth **/
            Intent TurnBTOn = new Intent((BluetoothAdapter.ACTION_REQUEST_ENABLE));
            startActivityForResult(TurnBTOn,1);
        }

        /** Set a listener object to the Bluetooth button **/
        btnPaired.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                pairedDevicesList();
            }
        });
    }

    /** **/
    private void pairedDevicesList(){
        pairedDevices = myBluetooth.getBondedDevices();
        ArrayList list = new ArrayList();

        /** Number of available devices is greater than 0 **/
        if(pairedDevices.size()>0){
            /** Loop through each available device and add to local list **/
            for(BluetoothDevice bt: pairedDevices){
                list.add("Name: " + bt.getName() +
                        "\nAddress: " + bt.getAddress());
            }
        }

        /** No bluetooth devices found **/
        else{
            Toast.makeText(getApplicationContext(),
                    "Bluetooth devices unavailable",
                    Toast.LENGTH_LONG);
        }

        final ArrayAdapter adapter = new ArrayAdapter(
                this, android.R.layout.simple_list_item_1,list);
        deviceList.setAdapter(adapter);
        deviceList.setOnItemClickListener(myListClickListener);
    }

    private AdapterView.OnItemClickListener myListClickListener =
            new AdapterView.OnItemClickListener() {

        public void onItemClick(AdapterView<?> av,
                                View v, int arg2, long arg3){
            /** Get the device MAC address, the last 17 chars in the View **/
            String info = ((TextView) v).getText().toString();
            String address = info.substring(info.length() - 17);

            /** Make an intent to start next activity. **/
            // ToDO: Update this.getClass() to Class for copter control
            Intent i = new Intent(DeviceList.this, this.getClass());

            /** Change the activity **/
            i.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity
            startActivity(i);
        }
    };


}
