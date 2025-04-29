<?php

namespace App\Config;

class Pusher
{
    public static function getConfig()
    {
        return [
            'app_id'  => '1952121',
            'key'     => '36674e0f0e9c186cdb52',
            'secret'  => '3a643d5cdbd60bc177e4',
            'cluster' => 'us2',
            'useTLS'  => true
        ];
    }
}
