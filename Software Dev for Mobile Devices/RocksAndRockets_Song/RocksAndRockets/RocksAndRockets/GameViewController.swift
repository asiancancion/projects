//
//  GameViewController.swift
//  RocksAndRockets
//
//  Created by Chad Mello on 2/6/20.
//  Copyright © 2020 Chad Mello. All rights reserved.
//

/*
 Name: Caleb Song
 Assignment: Pex 3
 Documentation: Used Chat GPT to debug and implement features: https://chatgpt.com/share/672e7f96-88a4-800e-9405-18c4c0a11a1d
 */

import UIKit
import SpriteKit

class GameViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        let scene = GameScene(size: view.bounds.size)
        let skView = view as! SKView
        skView.showsFPS = true
        skView.showsNodeCount = true
        skView.ignoresSiblingOrder = true
        scene.scaleMode = .resizeFill
        skView.presentScene(scene)
    }
    
    override var prefersStatusBarHidden: Bool {
        return true
    }
}
