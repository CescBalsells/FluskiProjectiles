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
 
https://user-images.githubusercontent.com/45798069/226691150-ca949e71-8d7e-40af-af6e-6f2207bb2350.mp4


 ### ExplosiveProjectile
 This projectile inherits from the BaseProjectile, includes diferent parameters used to manage the damage of an explosion and also a callback Event used when the    projectile explodes
 
https://user-images.githubusercontent.com/45798069/226693015-165d6678-9c6c-48ce-a7d6-53030d5f09ee.mp4


 ### ChargedProjectile
 This projectile inherits from the BaseProjectile, adds a min and a max damage that the projectile should deal depending on how charged it is when its thrown.
 
https://user-images.githubusercontent.com/45798069/226691589-1c3d25ce-3306-4b32-9150-5958a7728491.mp4


 ### GrenadeProecjtile
 This projectile inherits from the ExplosiveProjectile, a projectile that has an explosion timer and explodes when the timer finishes.
 
https://user-images.githubusercontent.com/45798069/226690718-2dad658e-7029-4ed7-a45f-2900a89c380d.mp4


 ## Gizmo Projecile
 As last but not less important ther's the Gizmo projectile which is used to determine the path that will follow the projectile and the hit location. The Gizmo is implemented on the Projectile Launcher blueprints that contains the plugin as example.

 



