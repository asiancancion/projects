//
//  GameScene.swift
//  RocksAndRockets
//
//  Created by Chad Mello on 2/6/20.
//  Copyright © 2020 Chad Mello. All rights reserved.
//

import SpriteKit

// Some operator overloads to deal with GCPoint vector ,math

//Go here for more info on simple vector math: https://www.mathsisfun.com/algebra/vectors.html
func +(left: CGPoint, right: CGPoint) -> CGPoint {
    return CGPoint(x: left.x + right.x, y: left.y + right.y)
}

func -(left: CGPoint, right: CGPoint) -> CGPoint {
    return CGPoint(x: left.x - right.x, y: left.y - right.y)
}

func *(point: CGPoint, scalar: CGFloat) -> CGPoint {
    return CGPoint(x: point.x * scalar, y: point.y * scalar)
}

func /(point: CGPoint, scalar: CGFloat) -> CGPoint {
    return CGPoint(x: point.x / scalar, y: point.y / scalar)
}

// no need to worry about this -
// This is a precompiler directive to tweak the
// sqrt function according to the processor/platform.
// Some older 32-bit devices (like anything older than 5S) cannot
// handle 64-bit Float types.
#if !(arch(x86_64) || arch(arm64))
func sqrt(a: CGFloat) -> CGFloat {
    return CGFloat(sqrtf(Float(a)))
}
#endif

// add some vector functionality to the CGPoint class...
extension CGPoint {
    func length() -> CGFloat {
        return sqrt(x*x + y*y)
    }
    
    func normalized() -> CGPoint {
        return self / length()
    }
}

// Our custom game scene...
class GameScene: SKScene {
    
    struct PhysicsCategory {
        static let none      : UInt32 = 0
        static let all       : UInt32 = UInt32.max
        static let rocket   : UInt32 = 0b1       // 1
        static let projectile: UInt32 = 0b10      // 2
        static let earth: UInt32 = 0b100
        static let player: UInt32 = 0b1000
        static let target: UInt32 = 0b10000
        static let ufo: UInt32 = 0b100000
    }
    
    //create the player node
    let player = SKSpriteNode(imageNamed: "player")
    let space = SKSpriteNode(imageNamed: "space")
    let ufo = SKSpriteNode(imageNamed: "ufo")
    let earth = SKSpriteNode(imageNamed: "globe")
    let target = SKSpriteNode(imageNamed: "green_dot")

    let earthHealthDisplay = SKLabelNode(fontNamed: "AvenirNext-Bold")
    let ufoHealthDisplay = SKLabelNode(fontNamed: "AvenirNext-Bold")
    let playerScoreDisplay = SKLabelNode(fontNamed: "AvenirNext-Bold")
    var rocketsDestroyed = 0
    var earthHealth = 100
    var ufoHealth = 100
    var playerHealth = 3
    
    override func didMove(to view: SKView) {
        
        // set our scene's background color
        
        //Display healths
        
        //Earth Health
        earthHealthDisplay.text = "Earth Health: \(earthHealth)"
        earthHealthDisplay.fontSize = 24
        earthHealthDisplay.fontColor = .red
        earthHealthDisplay.position = CGPoint(x: size.width - 700, y: size.height - 50)
        earthHealthDisplay.zPosition = 1
        addChild(earthHealthDisplay)
        
        //UFO Health
        ufoHealthDisplay.text = "UFO Health: \(ufoHealth)"
        ufoHealthDisplay.fontSize = 24
        ufoHealthDisplay.fontColor = .green
        ufoHealthDisplay.position = CGPoint(x: size.width - 704, y: size.height - 100)
        ufoHealthDisplay.zPosition = 1
        addChild(ufoHealthDisplay)
        
        //Player Score
        playerScoreDisplay.text = "Player Score: \(rocketsDestroyed)"
        playerScoreDisplay.fontSize = 24
        playerScoreDisplay.fontColor = .white
        playerScoreDisplay.position = CGPoint(x: size.width - 700, y: size.height - 150)
        playerScoreDisplay.zPosition = 1
        addChild(playerScoreDisplay)
        
        //Adding target dots
        target.size = CGSize(width: 75, height: 75)
        target.position = CGPoint(x: 0, y: ufo.size.height/4)
        target.zPosition = 5
        target.physicsBody = SKPhysicsBody(circleOfRadius: target.size.width / 2)
        target.physicsBody?.isDynamic = false
        target.physicsBody?.categoryBitMask = PhysicsCategory.target
        target.physicsBody?.contactTestBitMask = PhysicsCategory.projectile
        target.physicsBody?.collisionBitMask = PhysicsCategory.none
        target.isHidden = true;
        target.color = .green;
        target.colorBlendFactor = 1.0;
        ufo.addChild(target)
        
        
        
        
        //    backgroundColor = SKColor.black
        
        //space star background
        space.position = CGPoint(x: size.width / 2, y: size.height / 2)
        space.zPosition = -1
        space.size = size

        
        addChild(space)
        
        //set UFO
        ufo.position = CGPoint(x: size.width * 0.8, y: size.height * 0.8)
        ufo.zPosition = 2
        addChild(ufo)
        
        //UFO physics
        ufo.physicsBody = SKPhysicsBody(texture: ufo.texture!, size: ufo.size)
        ufo.physicsBody?.isDynamic = false
        ufo.physicsBody?.categoryBitMask = PhysicsCategory.ufo
        ufo.physicsBody?.contactTestBitMask = PhysicsCategory.projectile
        ufo.physicsBody?.collisionBitMask = PhysicsCategory.none
        
        //set UFO particles
        if let particleEmitter = SKEmitterNode(fileNamed: "UFOParticle") {
            
            particleEmitter.particleScale = 0.1
            particleEmitter.particleScaleRange = 0.02
            particleEmitter.particleScaleSpeed = 0.0
            particleEmitter.position = CGPoint(x: 0, y: -ufo.size.height)
            particleEmitter.zPosition = -1
            particleEmitter.targetNode = self
            ufo.addChild(particleEmitter)
        }
        
        //set Earth Physics
        earth.physicsBody = SKPhysicsBody(circleOfRadius: earth.size.width / 2)
        earth.physicsBody?.isDynamic = false
        earth.physicsBody?.categoryBitMask = PhysicsCategory.earth
        earth.physicsBody?.contactTestBitMask = PhysicsCategory.rocket
        earth.physicsBody?.collisionBitMask = PhysicsCategory.none
        
        //set Earth Display
        earth.position = CGPoint(x: size.width * 0.5, y: size.height * 0.001)
        let scale = max(size.width / earth.size.width, size.height / size.height)
        earth.setScale(scale)
        addChild(earth)
        
        let rotateAction = SKAction.rotate(byAngle: .pi * 2, duration: 30.0)
        let repeatRotation = SKAction.repeatForever(rotateAction)
        earth.run(repeatRotation)
        
        
        // center player in Y-axis
        player.position = CGPoint(x: size.width * 0.1, y: size.height * 0.5)
        
        //set player Physics
        player.physicsBody = SKPhysicsBody(circleOfRadius: player.size.width / 2)
        player.physicsBody?.isDynamic = false
        player.physicsBody?.categoryBitMask = PhysicsCategory.player
        player.physicsBody?.contactTestBitMask = PhysicsCategory.rocket
        player.physicsBody?.collisionBitMask = PhysicsCategory.none
        
        // add player to the scene
        addChild(player)
        
        //Player bounce
        let moveUp = SKAction.moveBy(x: 0, y: 30, duration: 1.5)
        let moveDown = SKAction.moveBy(x: 0, y: -30, duration: 1.5)
        let bounceSequence = SKAction.sequence([moveUp, moveDown])
        let repeatBounce = SKAction.repeatForever(bounceSequence)
        player.run(repeatBounce)
        
        // we're in space - so no gravity
        physicsWorld.gravity = .zero
        
        // we will handle user taps from here...
        physicsWorld.contactDelegate = self
        
        // add some background music
        let backgroundMusic = SKAudioNode(fileNamed: "background-music-aac.caf")
        backgroundMusic.autoplayLooped = true
        addChild(backgroundMusic)
        
        

        
        // Now, start the game loop
        run(SKAction.repeatForever(
            SKAction.sequence([
                SKAction.run(addRocket),
                SKAction.wait(forDuration: random(min: 1.0, max: 3.0))
            ])
        ))
        run(SKAction.repeatForever(
            SKAction.sequence([
                SKAction.run{self.showTarget() },
                SKAction.wait(forDuration: 2.0, withRange: 2.0)])))
    }
    
    //utility function for creating random number...
    func random() -> CGFloat
    {
        //Note: arc4random returns an unsigned integer up to (2^32)-1
        //      Here, we're forcing a return of a float between 0 and 1.
        return CGFloat(Float(arc4random()) / 0xFFFFFFFF)
    }
    
    func random(min: CGFloat, max: CGFloat) -> CGFloat {
        // return a random number between min and max, inclusive
        return random() * (max - min) + min
    }
    
    func addRocket() {
        
        // Create sprite for the rocket
        let rocket = SKSpriteNode(imageNamed: "rocket")
        
        // add physics simulation to the rocket node
        rocket.physicsBody = SKPhysicsBody(rectangleOf: rocket.size)
        
        // Affected by gravity, friction, collisions, etc..
        rocket.physicsBody?.isDynamic = true
        
        // belongs to the "rocket category"
        rocket.physicsBody?.categoryBitMask = PhysicsCategory.rocket
        
        // Here, we're interested in whether the rocker makes contact with a rock
        rocket.physicsBody?.contactTestBitMask = PhysicsCategory.projectile | PhysicsCategory.earth | PhysicsCategory.player
        
        // define which categories of physics bodies can collide with a rocket
        rocket.physicsBody?.collisionBitMask = PhysicsCategory.none
        
        // Determine where to spawn the rocket along the Y axis
        
//        let actualY = random(min: rocket.size.height/2, max: size.height - rocket.size.height/2)
        let actualX = ufo.position.x
        let actualY = ufo.position.y
        rocket.zPosition = 2
        // Position the rocket slightly off-screen along the right edge,
        // and along a random position along the Y axis as calculated above
//        rocket.position = CGPoint(x: size.width + rocket.size.width/2, y: actualY)
        rocket.position = CGPoint(x: actualX, y: actualY)
        
        // Add the rocket to the scene
        addChild(rocket)
        
        // Determine speed of the rocket...
        // can take between 2 and 4 seconds to go from one end of the screen to the other
        let actualDuration = random(min: CGFloat(2.0), max: CGFloat(4.0))
        
        // Create the actions...
        
        //Random locations
        
        let targetLocation = Int.random(in: 0...2)
        var locationX: CGFloat
        var locationY: CGFloat
        switch targetLocation{
        case 1:
            //Target player
            locationX = player.position.x
            locationY = player.position.y
            
        case 2:
            //Target Earth
            locationX = earth.position.x
            locationY = earth.position.y
        default:
            //Random
            locationX = random(min: rocket.size.height/2, max: size.height - rocket.size.height/2)
            locationY = random(min: rocket.size.height/2, max: size.height - rocket.size.height/2)
        }
        
        
        
        // setup an action to move the rocket from the right to the left, within a certian frame of time.
        let actionMove = SKAction.move(to: CGPoint(x: locationX, y: locationY), duration: TimeInterval(actualDuration))
        
        // When movement is complete, we want to remove the rocket from the scene (VERY IMPORTANT)
        let actionMoveDone = SKAction.removeFromParent()
        
        // This is what happens when the player loses (rocket gets past you)
        
        
        
        // In this clase we're creating a "closure" - or what many might know as a "lambda"
        let loseAction = SKAction.run() { [weak self] in //remember why we use "weak"?
            guard let `self` = self else { return } //
            let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
            let gameOverScene = GameOverScene(size: self.size, won: false)
            if (earthHealth == 0){
                self.view?.presentScene(gameOverScene, transition: reveal)
            }
        }
        
        // ok, set this new rocket node in motion with all of the actions we dfined above
        rocket.run(SKAction.sequence([actionMove, loseAction, actionMoveDone]))
    }
    //This function randomly pops the green dots on the UFO for the player to target
    func showTarget(){

        let randomX = CGFloat.random(in: -20 ... 20)
        let randomY = CGFloat.random(in: -25 ... 40)
        
        target.position = CGPoint(x: randomX, y: randomY)
        target.isHidden = false
        
        print("Target position:", target.position)
        
        target.run(SKAction.sequence([
            SKAction.wait(forDuration: 15.0),SKAction.run{self.target.isHidden = true}
        ]))
    }
    
    // User touched the screen to throw a rock, let's determine what to do from here...
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        // Choose one of the touches to work with
        guard let touch = touches.first else {
            return
        }
        run(SKAction.playSoundFileNamed("pew-pew-lei.caf", waitForCompletion: false))
        
        
        // Get player's projectile (i.e. a new rock) ready to launch
        
        let touchLocation = touch.location(in: self)
        
        // Set up initial location of projectile
        let projectile = SKSpriteNode(imageNamed: "projectile")
        projectile.position = player.position
        
        projectile.physicsBody = SKPhysicsBody(circleOfRadius: projectile.size.width/2)
        projectile.physicsBody?.isDynamic = true
        projectile.physicsBody?.categoryBitMask = PhysicsCategory.projectile
        projectile.physicsBody?.contactTestBitMask = PhysicsCategory.rocket | PhysicsCategory.ufo
        projectile.physicsBody?.collisionBitMask = PhysicsCategory.none
        projectile.physicsBody?.usesPreciseCollisionDetection = true
        
        // Determine offset of location to rock
        let offset = touchLocation - projectile.position
        
        // You cannot throw a rock down or backwards
        if offset.x < 0 { return }
        
        // add the new rock to the scene
        addChild(projectile)
        
        //Get the direction of where to shoot
        let direction = offset.normalized()
        
        // Make rock go far enough to be guaranteed off screen
        let shootAmount = direction * 1000
        
        // Add that distance to the current position
        let realDest = shootAmount + projectile.position
        
        // Create the actions to put this rock into motion
        let actionMove = SKAction.move(to: realDest, duration: 2.0)
        let actionMoveDone = SKAction.removeFromParent()
        projectile.run(SKAction.sequence([actionMove, actionMoveDone]))
    }
    
    // Here, we respond to a collision between rock and rocket.
    func projectileDidCollideWithrocket(projectile: SKSpriteNode, rocket: SKSpriteNode) {
        print("Hit")
        projectile.removeFromParent()
        rocket.removeFromParent()
        
        rocketsDestroyed += 1
        playerScoreDisplay.text = "Player Score: \(rocketsDestroyed)"
        //If player destroys 30 rockets game is over
        if rocketsDestroyed >= 30 {
            let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
            let gameOverScene = GameOverScene(size: self.size, won: true)
            view?.presentScene(gameOverScene, transition: reveal)
        }
    }
    //Collision between rocket and earth
    func projectileDidCollideWithearth(rocket: SKSpriteNode){
        print("Hit Earth")
        rocket.removeFromParent()
        
        //Add explosion and then remove after 1.5 seconds
        let explosion = SKSpriteNode(imageNamed: "earthBoom")
        explosion.position = rocket.position
        explosion.zPosition = 3
        explosion.setScale(0.5)
        addChild(explosion)

        let wait = SKAction.wait(forDuration: 2.0)
        let removeExplosion = SKAction.removeFromParent()
        let explosionSequence = SKAction.sequence([wait, removeExplosion])
        explosion.run(explosionSequence)
        
        //if rocket hits earth subtract 10 health
        earthHealth-=10
        earthHealthDisplay.text = "Earth Health: \(earthHealth)"
        if earthHealth == 0 {
            let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
            let gameOverScene = GameOverScene(size: self.size, won: false)
            view?.presentScene(gameOverScene, transition: reveal)
        }
    }
    //collision between rocket and player
    func projectileDidCollideWithplayer(rocket: SKSpriteNode){
        print("Hit Player")
        rocket.removeFromParent()
        //Add explosion and then remove after 1.5 seconds
        let explosion = SKSpriteNode(imageNamed: "explosionPlayer")
        explosion.position = rocket.position
        explosion.zPosition = 3
        explosion.setScale(0.5)
        addChild(explosion)
        let wait = SKAction.wait(forDuration: 1.5)
        let removeExplosion = SKAction.removeFromParent()
        let explosionSequence = SKAction.sequence([wait, removeExplosion])
        explosion.run(explosionSequence)
        //If player is hit 3 times then game ends
        playerHealth-=1
        if playerHealth == 0{
            let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
            let gameOverScene = GameOverScene(size: self.size, won: false)
            view?.presentScene(gameOverScene, transition: reveal)
        }
    }
    //collision between UFO and rock (if the green target is hit)
    func projectileDidCollideWithUFO(projectile: SKSpriteNode, target: SKSpriteNode){
        print("Hit UFO")
        projectile.removeFromParent()

        //Add explosion and then remove after 1.5 seconds
        let explosion = SKSpriteNode(imageNamed: "explosion_small")
        explosion.position = projectile.position
        explosion.zPosition = 3
        explosion.setScale(0.5)
        addChild(explosion)
        let wait = SKAction.wait(forDuration: 1.5)
        let removeExplosion = SKAction.removeFromParent()
        let explosionSequence = SKAction.sequence([wait, removeExplosion])
        explosion.run(explosionSequence)
        target.isHidden = true
        
        //subtract 10 health from UFO and if UFO is at 0 health then game is over and player score increases by 1000
        ufoHealth-=10
        ufoHealthDisplay.text = "UFO Health: \(ufoHealth)"
        if ufoHealth == 0{
            rocketsDestroyed+=1000
            playerScoreDisplay.text = "Player Score: \(rocketsDestroyed)"
            //if UFO is destroyed make big explosion and then end the game
            let final_explosion = SKSpriteNode(imageNamed: "bigexplosion")
            final_explosion.position = projectile.position
            final_explosion.zPosition = 5
            final_explosion.setScale(2.0)
            addChild(final_explosion)
            
            let gameFreezeWait = SKAction.wait(forDuration: 3.0)
            let transitionToGameOver = SKAction.run { [weak self] in
                guard let self = self else { return }
                let reveal = SKTransition.flipHorizontal(withDuration: 0.5)
                let gameOverScene = GameOverScene(size: self.size, won: true)
                self.view?.presentScene(gameOverScene, transition: reveal)
            }
            
            run(SKAction.sequence([gameFreezeWait, transitionToGameOver]))
        }
    }
    
}

// Here, we're told that two objects made contact
extension GameScene: SKPhysicsContactDelegate {
    func didBegin(_ contact: SKPhysicsContact) {
        // Let's get at the objects that made contact...
        var firstBody: SKPhysicsBody
        var secondBody: SKPhysicsBody
        if contact.bodyA.categoryBitMask < contact.bodyB.categoryBitMask {
            firstBody = contact.bodyA
            secondBody = contact.bodyB
        } else {
            firstBody = contact.bodyB
            secondBody = contact.bodyA
        }
        
        
        // respond if we determine that a rock and rocket made contact
        if ((firstBody.categoryBitMask & PhysicsCategory.rocket != 0) &&
            (secondBody.categoryBitMask & PhysicsCategory.projectile != 0)) {
            if let rocket = firstBody.node as? SKSpriteNode,
               let projectile = secondBody.node as? SKSpriteNode {
                projectileDidCollideWithrocket(projectile: projectile, rocket: rocket)
            }
        }
        // Check if a rocket collided with the earth
        if (firstBody.categoryBitMask & PhysicsCategory.rocket != 0) &&
            (secondBody.categoryBitMask & PhysicsCategory.earth != 0) {
            if let rocket = firstBody.node as? SKSpriteNode {
               projectileDidCollideWithearth(rocket: rocket)
            }
        }
        //rocket collided with player
        if (firstBody.categoryBitMask & PhysicsCategory.rocket != 0) &&
            (secondBody.categoryBitMask & PhysicsCategory.player != 0) {
            if let rocket = firstBody.node as? SKSpriteNode {
               projectileDidCollideWithplayer(rocket: rocket)
            }
        }
        //rock and target collided
        if (firstBody.categoryBitMask & PhysicsCategory.projectile != 0) &&
            (secondBody.categoryBitMask & PhysicsCategory.target != 0) && !target.isHidden {
            if let projectile = firstBody.node as? SKSpriteNode,
               let target = secondBody.node as? SKSpriteNode{
                projectileDidCollideWithUFO(projectile: projectile, target: target)
            }
        }
    }
}
