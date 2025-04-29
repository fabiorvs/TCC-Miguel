<?php

use CodeIgniter\Router\RouteCollection;

/**
 * @var RouteCollection $routes
 */
$routes->get('/', 'Home::index');


$routes->post('api/sensores', 'SensorController::create');

$routes->post('api/logs', 'LogController::create');
$routes->get('api/logs', 'LogController::index');
