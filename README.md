# FluskiProjectiles
 
 The Plug-in includes the FluskiProjectileMovementComponent and the 5 Projectile Actors.
 
 ![FluskiProjectilesPlugin](https://user-images.githubusercontent.com/45798069/226667933-d7fa6bb9-52dd-44cd-953e-ef551683b5f9.PNG)
 
 ## FluskiProjectileMovementComponent
 This Movement Component inherits from the Unreal ProjectileMovementComponent and adds some extra features:
 
 1. Charged Speed: The Initial Speed of the projectile is determined by how charged is the projectile. Being 1 max speed and 0 min speed.
 2. Distance: Broadcast an event when the projectile reached certain distance.
 3. HominDistance: If the Projectile has a HomingTarget only will be applied when the projectile is inside the determined distance range from it's target.
 
Unlike the normal ProjectileMovementComponent this one has to be thrown using the function ThrowProjectile, without using this function the projectile will not start moving.
 
 ## Projectiles
 
 The plugin also includes diferent type of projectiles that can be used as Actors, and are already setted.
 
 ### BaseProjectile
 Base class of the projectiles which has the basic funcions as the spawn and Throw ones. The other projectiles inherit from this base class.
 
 
 ### DamageProjectile
 This projectile inherits from the BaseProjectile and includes a Damage Value that can be used to DealDamage after a collision with an enemy.
 
![Damage](https://user-images.githubusercontent.com/45798069/226693996-129ca05e-af26-40cc-8c58-a4ebf6b2f211.gif)


 ### ExplosiveProjectile
 This projectile inherits from the BaseProjectile, includes diferent parameters used to manage the damage of an explosion and also a callback Event used when the    projectile explodes

![Explosive](https://user-images.githubusercontent.com/45798069/226694038-11b10b97-b627-4ea2-aace-607a4c211ea2.gif)


 ### ChargedProjectile
 This projectile inherits from the BaseProjectile, adds a min and a max damage that the projectile should deal depending on how charged it is when its thrown.
 
![Charged](https://user-images.githubusercontent.com/45798069/226694073-17498682-41b0-4e51-917d-1d098087ed0b.gif)


 ### GrenadeProecjtile
 This projectile inherits from the ExplosiveProjectile, a projectile that has an explosion timer and explodes when the timer finishes.
 
![Grenade](https://user-images.githubusercontent.com/45798069/226694098-b0e2e4bb-af9c-4447-b6b3-05114245efbf.gif)


 ## Gizmo Projecile
 As last but not less important ther's the Gizmo projectile which is used to determine the path that will follow the projectile and the hit location. The Gizmo is implemented on the Projectile Launcher blueprints that contains the plugin as example.

 



