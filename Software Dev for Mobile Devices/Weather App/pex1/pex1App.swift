//
//  pex1App.swift
//  pex1
//
//  Created by Caleb Song on 9/23/24.
//

import SwiftUI

@main
struct pex1App: App {
    var body: some Scene {
        WindowGroup {
            ContentView(locationManager: LocationManager())
        }
    }
}
