//
//  BTService.swift
//  Arduino_Servo
//
//  Created by yuanfeng on 16/2/21.
//  Copyright © 2016年 Razeware LLC. All rights reserved.
//
import Foundation
import CoreBluetooth

/* Services & Characteristics UUIDs */
let BLEServiceUUID = CBUUID(string: "DF977B84-FC23-0A07-77D9-2E2C92AB1A27")
let PositionCharUUID = CBUUID(string: "FF7BCE6D-5A8F-4FFA-8D20-8BF29999A5FB")
let BLEServiceChangedStatusNotification = "kBLEServiceChangedStatusNotification"

class BTService: NSObject, CBPeripheralDelegate {
  var peripheral: CBPeripheral?
  var positionCharacteristic: CBCharacteristic?
  
  init(initWithPeripheral peripheral: CBPeripheral) {
    super.init()
    
    self.peripheral = peripheral
    self.peripheral?.delegate = self
  }
  
  deinit {
    self.reset()
  }
  
  func startDiscoveringServices() {
    self.peripheral?.discoverServices([BLEServiceUUID])
  }
  
  func reset() {
    if peripheral != nil {
      peripheral = nil
    }
    
    // Deallocating therefore send notification
    self.sendBTServiceNotificationWithIsBluetoothConnected(false)
  }
  
  // Mark: - CBPeripheralDelegate
  
  func peripheral(peripheral: CBPeripheral, didDiscoverServices error: NSError?) {
    let uuidsForBTService: [CBUUID] = [PositionCharUUID]
    
    if (peripheral != self.peripheral) {
      // Wrong Peripheral
      return
    }
    
    if (error != nil) {
      return
    }
    
    if ((peripheral.services == nil) || (peripheral.services!.count == 0)) {
      // No Services
      return
    }
    
    for service in peripheral.services! {
      if service.UUID == BLEServiceUUID {
        peripheral.discoverCharacteristics(uuidsForBTService, forService: service)
      }
    }
  }
  
  func peripheral(peripheral: CBPeripheral, didDiscoverCharacteristicsForService service: CBService, error: NSError?) {
    if (peripheral != self.peripheral) {
      // Wrong Peripheral
      return
    }
    
    if (error != nil) {
      return
    }
    
    if let characteristics = service.characteristics {
      for characteristic in characteristics {
        if characteristic.UUID == PositionCharUUID {
          self.positionCharacteristic = (characteristic)
          peripheral.setNotifyValue(true, forCharacteristic: characteristic)
          
          // Send notification that Bluetooth is connected and all required characteristics are discovered
          self.sendBTServiceNotificationWithIsBluetoothConnected(true)
        }
      }
    }
  }
  
  // Mark: - Private
  
//  func writePosition(position: UInt8) {
//    
//    /******** (1) CODE TO BE ADDED *******/
//    
//  }
    func writePosition(position: UInt8) {
        // See if characteristic has been discovered before writing to it
        if let positionCharacteristic = self.positionCharacteristic {
            // Need a mutable var to pass to writeValue function
            var positionValue = position
            let data = NSData(bytes: &positionValue, length: sizeof(UInt8))
            self.peripheral?.writeValue(data, forCharacteristic: positionCharacteristic, type: CBCharacteristicWriteType.WithResponse)
        }
    }
  
  func sendBTServiceNotificationWithIsBluetoothConnected(isBluetoothConnected: Bool) {
    let connectionDetails = ["isConnected": isBluetoothConnected]
    NSNotificationCenter.defaultCenter().postNotificationName(BLEServiceChangedStatusNotification, object: self, userInfo: connectionDetails)
  }
  
}